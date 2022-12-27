echo "building..."
g++ src/main.cpp src/files/wav/openWav.cpp src/display/window.cpp \
    src/display/tab.cpp src/imgui/misc/cpp/imgui_stdlib.cpp src/display/data.cpp src/dsp/fft.cpp \
    -I"./src" -I"./src/include" \
    -L"./build" -lsfml-graphics -lsfml-window -lsfml-system -lImGui-SFML -lpthread\
    -o build/sig.out -std=c++2a
echo "done building."