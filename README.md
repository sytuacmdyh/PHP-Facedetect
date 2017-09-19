# PHP-Facedetect
A simple OpenCV wrapper for PHP to detect faces on images

OpenCV 3 Support

---------------------------------------------------------------------------------

## my comments:
environment: centos7.2 + opencv3.1.0 + php7

### shell:
1. yum install gtk+-devel.x86_64   gimp-devel.x86_64  gimp-devel-tools.x86_64   gimp-help-browser.x86_64 zlib-devel.x86_64  libtiff-devel.x86_64  libjpeg-devel.x86_64 libpng-devel.x86_64  gstreamer-devel.x86_64  libavc1394-devel.x86_64  libraw1394-devel.x86_64 libdc1394-devel.x86_64  jasper-devel.x86_64 jasper-utils.x86_84  swig  python  libtool  nasm.x86_84
2. cd opencv3.1.0
3. cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_NEW_PYTHON_SUPPORT=NO .
> (you may need to download ippicv_linux_20151201.tgz since the great wall. and than, copy to opencv-3.1.0/3rdparty/ippicv/downloads/linux-808b791a6eac9ed78d32a7666804320e/)
4. make && make install
5. echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf && ldconfig
6. echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig" >> /etc/bashrc
7. echo "export PKG_CONFIG_PATH" >> /etc/bashrc
8. source /etc/bashrc
9. phpize && ./configure && make && make install

### export function name:
object_detect($picture_body, $path_of_xml, $minNeighbors);//if you don't know what is $minNeighbors, just fill 2
object_count($picture_body, $path_of_xml, $minNeighbors);//if you don't know what is $minNeighbors, just fill 2
