echo "building..."
g++ src/main.cpp src/files/wav/openWav.cpp src/display/window.cpp \
    src/display/tab.cpp src/imgui/misc/cpp/imgui_stdlib.cpp src/display/data.cpp src/dsp/fft.cpp \
    src/display/tabs/waterfall.cpp src/display/tabs/waveform.cpp src/dsp/windowing.cpp\
    -I"./src" -I"./src/include" \
    -L"./build" -lsfml-graphics -lsfml-window -lsfml-system -lImGui-SFML\
    -o build/sig -std=c++2a
echo "done building."

echo "setting up xwindow"
cd build
export DISPLAY=$(route.exe print | grep 0.0.0.0 | head -1 | awk '{print $4}'):0.0

echo "running app"
./sig

echo "app closed"
cd ..
rm ./build/sig