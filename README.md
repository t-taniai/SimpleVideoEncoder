# SimpleVideoEncoder

Encode an image sequence in a folder into a video using OpenCV's ffmpeg.

## Dependencies
- OpenCV 3.0 or higher (Hopefully this will be automatically downloaded by Nu Package Manager in Visual Studio).
- Visual Studio 2013 (x64 build)
- OpenH264 (OpenCV 3.1 will require [openh264-1.4.0-win64msvc](https://github.com/cisco/openh264/releases))
- Windows OS (for Win32 APIs of file IO)

## Usage
>  Encoder.exe -inputDir directoryPath

Or drag & drop a folder onto the encoder_H264.bat file.

Options and default values in []:
- -inputDir (required)
- -outputFile [inputDir\output.avi]
- -filePattern [*.png]
- -fps [29.970000]
- -resizeScale [1.000000]
- -startFrame [0]
- -endFrame [-1]
- -trimEnd [0]
- -fourcc [H264]

## History
- 2016/08/25 Released
