{
  "targets": [
    {
      "target_name": "brctl",
      "sources": [ "brctl.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
