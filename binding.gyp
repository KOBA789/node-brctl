{
  "targets": [
    {
      "target_name": "brctl",
      "sources": [ "brctl.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "libbridge"
      ],
      "dependencies": [ "libbridge" ]
    },
    {
      "target_name": "libbridge",
      "type": "static_library",
      "sources": [
        "libbridge_devif.c",
        "libbridge_if.c",
        "libbridge_init.c",
        "libbridge_misc.c"
      ],
      "include_dirs": [
        "/usr/src/linux/include"
      ]
    }
  ]
}
