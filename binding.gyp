{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "hello.cpp" ],
      "libraries+": [
        "<!@(pkg-config --libs Baloo)",
      ],
      "cflags+":[
        "<!@(pkg-config --cflags Baloo)",
      ],
    }
  ]
}
