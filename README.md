# UIRibbon-Reversing

## About
This is my playground reverse-engineering the proprietary binary UIRibbon resource blobs.
Since Win7 applications can can use the ribbon framework to create Office-like ribbons. Those ribbons are defined in an xml file and then compiled into some proprietary binary blob that then is used by the runtime to generate the ribbon.

Basically, the goal of this project is to understand and be able to parse the format, so we can can make a reimplementation of the ribbon logic in WINE.

Since this is an hobby project and I'm not too familiar with reverse engineering, it's a fairly ambitious topic, and I'm not sure how fast (if at all) I can achieve the goal.

## State

Up to now nearly nothing is really decoded properly, 99% of the data is just read as-is. If you're looking to understand the format, maybe check back in 1-2 years or so.

## Development

The project uses Kaitai Struct to describe the structure of the binaries. The primary goal is to use Kaitai Struct to write a complete specification - which then later can be used to write or generate a parser.

Development is almost fully done on linux through blackbox testing. Testing is done by writing an xml file and running it through UICC (Part of win7 SDK), then comparing the outputs for different xml files. It's possible, but it's very tedious work. 

If you're curious, yes, UICC works under wine: You need UICC.exe + UICCDLL.dll, and "winetricks -q msxml3 msxml6".
