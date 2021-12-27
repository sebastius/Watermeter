# Watermeter
watermeter

Udev rules: 

* lsusb
* sudo -s
* echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", SYMLINK="ttyWatertrekker"' >> /etc/udev/rules.d/99-serialmeuk.rules
