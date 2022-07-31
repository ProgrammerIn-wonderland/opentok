# Opentok C++

This is the folder containing everything you need to use freetok for C++

---

To use this library, you require two libraries on your system
* [Nholmann JSON](https://json.nlohmann.me/) - [Archlinux package](https://archlinux.org/packages/community/any/nlohmann-json/)
* [libCURL](https://curl.se/) - [Archlinux package](https://archlinux.org/packages/core/x86_64/curl/)

Once these two are installed, compilation is super simple,

just use your favored compiler (g++ used for example) to compile the C++ code

`g++ main.cpp -O3 -lcurl -o freetok`

and then execute the program with the URL as the argument

`./freetok "https://www.tiktok.com/@yukine_y9/video/7068592756599426306"`

this will output a link to an mp4 url, to watch the video, you can try to view the video in mpv

`mpv $(./freetok "https://www.tiktok.com/@yukine_y9/video/7068592756599426306")`

this should open an mpv window with your tiktok video
