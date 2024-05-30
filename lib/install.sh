conan profile new default --detect
conan profile update settings.compiler.version=11 default
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install .. --build=missing

echo "gtest version:" $(pkg-config --modversion gtest)
echo "spdlog version:" $(pkg-config --modversion spdlog)
echo "libconfig version:" $(pkg-config --modversion libconfig)
echo "yaml-cpp version:" $(pkg-config --modversion yaml-cpp)
echo "boost version:" $(pkg-config --modversion boost)