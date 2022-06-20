echo "building..."
g++ src/main.cpp -L"./build" -lsfml-graphics -lsfml-window -lsfml-system -lImGui-SFML -o build/sig
echo "done building."

echo "setting up xwindow"
export DISPLAY=$(route.exe print | grep 0.0.0.0 | head -1 | awk '{print $4}'):0.0

echo "running app"
./build/sig

echo "app closed"