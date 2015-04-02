# Toshiba\_CT-90287-TV remote control configuration #
LIT9 was tested with a Toshiba\_CT-90287-TV remote control, according to the following configuration.

You can insert these lines in: /etc/lirc/lircd.conf
```
# /etc/lirc/lircd.conf
begin remote
  name  LITtoshiba
  bits           16
  flags SPACE_ENC|CONST_LENGTH
  eps            30
  aeps          100
  header       8991  4371
  one           606  1622
  zero          606   498
  ptrail        590
  pre_data_bits   16
  pre_data       0x2FD
  gap          107916
  toggle_bit_mask 0x0
      begin codes
          power                    0x48B7
          1                        0x807F
          2                        0x40BF
          3                        0xC03F
          4                        0x20DF
          5                        0xA05F
          6                        0x609F
          7                        0xE01F
          8                        0x10EF
          9                        0x906F
          0                        0x00FF
          back                     0x4AB5
          source                   0x28D7
          mute                     0x08F7
          vol+                     0x58A7
          vol-                     0x7887
          ch+                      0xD827
          ch-                      0xF807
          menu                     0xDA25
          exit                     0xC23D
          up                       0x9867
          down                     0xB847
          left                     0x42BD
          right                    0x02FD
          ok                       0x847B
          guide                    0xA25D
          tv/fav/radio             0xE21D
          red                      0x12ED
          green                    0x926D
          yellow                   0x52AD
          blue                     0xD22D
          widescreen               0x9A65
          picture_preset           0x8877
          info                     0x6897
          text                     0xE817
          subtitle                 0x30CF
          text_subpage             0x34CB
          stillpicture             0x44BB
      end codes
end remote
```