{
  "targets": [
    {
      "target_name": "baloo",
      "sources": [ "src/balooaddon.cpp", "src/query.cpp" ],
      "libraries+": [
        "<!@(pkg-config --libs Baloo)",
      ],
      "cflags+":[
        "<!@(pkg-config --cflags Baloo)",
      ],
    }
  ]
}
