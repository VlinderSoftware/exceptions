# Installing `exceptions`

The library uses CMake as its build system. The minimum required version is
CMake 3.8
You can configure with:
```
cmake -H. -Bbuild -DCMAKE_INSTALL_PREFIX=/path/to/install/exceptions
```
and build and install with:
```
cmake --build build --target install
```

If for any reason you want to regenerate the source `.tar.gz` and `.zip` packages:
```
cmake --build build --target package_source
```
