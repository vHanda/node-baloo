{
  "targets": [
    {
      "target_name": "baloo",
      "sources": [ "balooaddon.cpp", "query.cpp" ],
      "libraries+": [
        "<!@(pkg-config --libs Baloo)",
      ],
      "cflags+":[
        "<!@(pkg-config --cflags Baloo)",
      ],
    }
  ]
}
