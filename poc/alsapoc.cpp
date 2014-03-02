#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <alsa/asoundlib.h>

struct CallbackData
{
    int16_t *buffer;
    snd_pcm_uframes_t periodSize;
} typedef CallbackData;

void AlsaCallback(snd_async_handler_t *pcmCallback)
{
    snd_pcm_t *handle = snd_async_handler_get_pcm(pcmCallback);
    snd_pcm_uframes_t available;

    CallbackData *callbackData = 
        (CallbackData *)snd_async_handler_get_callback_private(pcmCallback);

    available = snd_pcm_avail_update(handle);
    while(available >= callbackData->periodSize) {
        snd_pcm_mmap_writei(handle, callbackData->buffer,
                callbackData->periodSize);
        available = snd_pcm_avail_update(handle);
        if(available < 0) {
            std::cout << "Buffer underrun" << std::endl;
            snd_pcm_prepare(handle);
        }
    }
}

int main(int argc, char *argv[])
{
    int32_t error;
    snd_pcm_t *handle = nullptr;
    std::string deviceName("hw:1");

    if(argc == 2)
        deviceName = std::string(argv[1]);

    // Opening the device
    error = snd_pcm_open(&handle, deviceName.c_str(), SND_PCM_STREAM_PLAYBACK,
            0);
    std::cout << "snd_pcm_open: " << snd_strerror(error) << std::endl;

    // Prepare setting hardware parameters
    snd_pcm_hw_params_t *hwParams = nullptr;
    snd_pcm_hw_params_malloc(&hwParams);
    snd_pcm_hw_params_any(handle, hwParams);

    // Set hardware parameters
    uint32_t bitrate = 48000;
    snd_pcm_uframes_t periodSize = 128;
    snd_pcm_uframes_t bufferSize = 8*periodSize;
    error = snd_pcm_hw_params_set_access(handle, hwParams,
            SND_PCM_ACCESS_MMAP_INTERLEAVED);
    std::cout << "snd_pcm_hw_params_set_access: " << snd_strerror(error) <<
        std::endl;
    error = snd_pcm_hw_params_set_format(handle, hwParams,
            SND_PCM_FORMAT_S16_LE);
    std::cout << "snd_pcm_hw_params_set_format: " << snd_strerror(error) <<
        std::endl;
    error = snd_pcm_hw_params_set_rate_near(handle, hwParams, &bitrate, 0);
    std::cout << "snd_pcm_hw_params_set_rate_near: " << snd_strerror(error) <<
        " actual: " << bitrate << std::endl;
    error = snd_pcm_hw_params_set_channels(handle, hwParams, 2);
    std::cout << "snd_pcm_hw_params_set_channels: " << snd_strerror(error)
        << std::endl;
    error = snd_pcm_hw_params_set_buffer_size_near(handle, hwParams, 
            &bufferSize);
    std::cout << "snd_pcm_hw_params_set_buffer_size_near: " <<
        snd_strerror(error) << " actual: " << bufferSize << std::endl;
    error = snd_pcm_hw_params_set_period_size_near(handle, hwParams,
            &periodSize, nullptr);
    std::cout << "snd_pcm_hw_params_set_period_size_near: " <<
        snd_strerror(error) << " actual: " << periodSize << std::endl;

    // Apply hardware parameters
    snd_pcm_hw_params(handle, hwParams);
    std::cout << "snd_pcm_hw_params: " << snd_strerror(error) << std::endl;

    // Free hardware parameters struct
    snd_pcm_hw_params_free(hwParams);

    // Prepare setting software parameters
    snd_pcm_sw_params_t *swParams;
    snd_pcm_sw_params_malloc(&swParams);
    snd_pcm_sw_params_current(handle, swParams);

    // Set software parameters
    snd_pcm_sw_params_set_start_threshold(handle, swParams, bufferSize -
            periodSize);
    std::cout << "snd_pcm_sw_params_set_start_threshold: " <<
        snd_strerror(error) << std::endl;
    snd_pcm_sw_params_set_avail_min(handle, swParams, periodSize);
    std::cout << "snd_pcm_sw_params_set_avail_min: " << snd_strerror(error) <<
        std::endl;

    // Apply software parameters
    snd_pcm_sw_params(handle, swParams);
    std::cout << "snd_pcm_sw_params: " << snd_strerror(error) << std::endl;

    // Free software parameters struct
    snd_pcm_sw_params_free(swParams);

    // Prepare device
    snd_pcm_prepare(handle);

    // Create buffer
    // Note: This is not the buffer alsa uses for playing sound, but our own
    // buffer where we read the data from that we are passing on to alsa.
    // We allocate: 2 channels * periodSize amount of frames * size of sample
    int16_t *buffer = (int16_t *)malloc(2*periodSize*sizeof(int16_t));
    // Simple square wave, frequency will deviate with the periodSize.
    for(uint32_t i = 0; i < periodSize; i++)
        buffer[i] = 0x7FFF;
    for(uint32_t i = periodSize; i < 2*periodSize; i++)
        buffer[i] = 0x0000;

    // Write initial chunk (twice the periodSize)
    error = snd_pcm_mmap_writei(handle, &buffer, periodSize);
    if(error > 0)
        std::cout << "snd_pcm_mmap_writei: " << error << " frames written" <<
            std::endl;
    else
        std::cout << "snd_pcm_mmap_writei: " << snd_strerror(error) <<
            std::endl;
    error = snd_pcm_mmap_writei(handle, &buffer, periodSize);
    if(error > 0)
        std::cout << "snd_pcm_mmap_writei: " << error << " frames written" <<
            std::endl;
    else
        std::cout << "snd_pcm_mmap_writei: " << snd_strerror(error) <<
            std::endl;

    // Set up callback data struct
    CallbackData *callbackData = (CallbackData *)malloc(sizeof(CallbackData));
    callbackData->buffer = buffer;
    callbackData->periodSize = periodSize;

    // Set asynchronous handler
    snd_async_handler_t *pcmCallback = nullptr;
    error = snd_async_add_pcm_handler(&pcmCallback, handle, AlsaCallback,
            callbackData);
    std::cout << "snd_async_add_pcm_handler: " << snd_strerror(error) <<
        std::endl;

    // Start playing
    error = snd_pcm_start(handle);
    std::cout << "snd_pcm_start: " << snd_strerror(error) << std::endl;

    // Loop forever
    while(true)
        sleep(1);

    // Clean up our buffer and callback data
    free(buffer);
    free(callbackData);

    // Stop playback
    error = snd_pcm_drain(handle);
    std::cout << "snd_pcm_drain: " << snd_strerror(error) << std::endl;

    // Closing the device
    snd_pcm_close(handle);
}
