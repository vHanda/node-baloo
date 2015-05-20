{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "hello.cpp" ],
      "include_dirs+": [
        "/home/vishesh/kde5/include/KF5/Baloo",
      ],
      "libraries+": [
        "-lKF5Baloo",
        "-L/usr/lib/",
        "<!@(pkg-config --libs Qt5Core)",
      ],
      "cflags":[
        "<!@(pkg-config --cflags Qt5Core)",
      ],
    }
  ]
}
