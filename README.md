# opencv_basics
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
mkdir build_opencv
cd build_opencv
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules -DPYTHON_DEFAULT_EXECUTABLE=$(which python3) -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON ../opencv
