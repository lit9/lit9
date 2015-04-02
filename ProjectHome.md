# **What is Lit9** #
Lit9 is an open source human computer interface; its main goal is to interact with a Linux system using a standard TV remote control as an input device.<br>
It is based on LIRC and it uses standard Xlib native functions to simulate mouse and keyboard (by means of predictive text technology) on the X Window System. <br>
It currently works on Ubuntu 9.x/10.x; it is tested with a standard MCE Kit (remote control and receiver) and with a generic remote control (Toshiba_CT-90287-TV), with USB-UIRT2 as receiver.<br>
<br>
<br>
<h1><b>Software requirements</b></h1>
To compile and run the current version of LIT 9 you should have Ubuntu 9.04, 9.10, 10.04 or 10.10.<br>
The main packages and libraries you need to install are:<br>
<br>
<i><br>
<ul><li>dialog<br>
</li><li>libqt4-dev<br>
</li><li>libqt4-core<br>
</li><li>libqt4-gui<br>
</li><li>libsqlite3-dev<br>
</li><li>lirc<br></i></li></ul>



The command you have to write in the shell to do everything in only one instruction is:<br>
<pre><code>    sudo apt-get install dialog libqt4-dev libqt4-core libqt4-gui libsqlite3-dev lirc<br>
</code></pre>

Or if there are any kind of problems:<br>
<br>
<pre><code>    sudo apt-get install dialog<br>
    sudo apt-get install libqt4-dev<br>
    sudo apt-get install libqt4-core<br>
    sudo apt-get install libqt4-gui<br>
    sudo apt-get install libsqlite3-dev<br>
    sudo apt-get install lirc<br>
</code></pre>


<h1><b>Other files needed</b></h1>
Inside /usr/share/lirc/ you have the configuration files of all remote controls you can use with lirc. We tested our system on a generic MCE (Windows Media Center) remote control with its relative receiver. <br>
The configuration of the buttons we used is easily reachable with this path:<br>
<br>
<br>
<pre><code>     gedit /usr/share/lirc/remotes/mceusb/lircd.conf.mceusb<br>
</code></pre>



To use it you have to edit a file called hardware.conf:<br>
<br>
<br>
<pre><code>     gedit /etc/lirc/hardware.conf<br>
</code></pre>



which must looks like this:<br>
<br>
<pre><code><br>
TRANSMITTER="Microsoft Windows Media Center V2 (usb) : Direct TV Receiver"<br>
TRANSMITTER_MODULES="lirc_dev mceusb"<br>
TRANSMITTER_DRIVER=""<br>
TRANSMITTER_DEVICE=""<br>
TRANSMITTER_SOCKET=""<br>
TRANSMITTER_LIRCD_CONF="directtv/general.conf"<br>
TRANSMITTER_LIRCD_ARGS=""<br>
START_LIRCD="true"<br>
START_LIRCMD=""<br>
LOAD_MODULES=""<br>
LIRCMD_CONF=""<br>
FORCE_NONINTERACTIVE_RECONFIGURATION="false"<br>
REMOTE="Windows Media Center Transceivers/Remotes (all)"<br>
REMOTE_MODULES="lirc_dev mceusb"<br>
REMOTE_DRIVER=""<br>
REMOTE_DEVICE="/dev/lirc0"<br>
REMOTE_SOCKET=""<br>
REMOTE_LIRCD_CONF="mceusb/lircd.conf.mceusb"<br>
REMOTE_LIRCD_ARGS="" <br>
</code></pre>

If you want you can download this file and the one used for Toshiba_CT-90287-TV remote control with USB-UIRT2 as receiver you can visit: <a href='http://code.google.com/p/lit9/w/list'>LiT9 Wiki</a>

<h1><b>A simple test</b></h1>
To test if everithing goes well you only have to connect the receiver to your computer and write this in the shell:<br>
<br>
<pre><code>name@pc-name:~$ irw<br>
</code></pre>

now if you press any button on the remote control you should see something like this:<br>
<pre><code>  name@pc-name:~$ 000000037ff07bfe 00 One mceusb<br>
  name@pc-name:~$ 000000037ff07bfd 00 Two mceusb<br>
  name@pc-name:~$ 000000037ff07bfc 00 Three mceusb<br>
  ..............................................<br>
</code></pre>

<h1><b>Source</b></h1>
The homepage of LiT 9 hosted on google code is at this link <a href='http://code.google.com/p/lit9/'>http://code.google.com/p/lit9/</a>

<h1><b>Donwload and Install</b></h1>
Last stable version tested and the user manual are available on: <a href='http://code.google.com/p/lit9/downloads/list'>Download section</a>

To extract files:<br>
<br>
<pre><code>name@pc-name:~$ tar xvzf lit9_vX.X.tar.gz<br>
name@pc-name:~$ cd lit9_vX.X<br>
</code></pre>

To compile LIT9:<br>
<br>
<pre><code>name@pc-name:~/lit9_vX.X$ qmake -project<br>
</code></pre>
<pre><code>name@pc-name:~/lit9_vX.X$ qmake<br>
</code></pre>

At this point you have to open the Makefile:<br>
<pre><code>name@pc-name:~/lit9_vX.X$ gedit Makefile<br>
</code></pre>

and modify a line before saving it:<br>
<pre><code>LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread <br>
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread -lX11 -lsqlite3<br>
</code></pre>

Make and run LIT9:<br>
<pre><code>name@pc-name:~/lit9_vX.X$ make<br>
</code></pre>
<pre><code>name@pc-name:~/lit9_vX.X$ ./lit9_vX.X<br>
<br>
</code></pre>

<h1><b>Notes</b></h1>
With other remote controls and receivers you have to download the lirc package which is on: <a href='http://www.lirc.org/'>http://www.lirc.org/</a> and also to see which is the right configuration for your system. <br>
Read the INSTALL file inside the package to start the configuration. The main variable you have to set are: <br><br>REMOTE_MODULES (modules to let your receiver talk with your pc) <br>REMOTE_LIRCD_CONF (where is the configuration of your remote control)<br>
<br>
<br>
<h1><b>About us</b></h1>
The software is taken from a student project, it is developed at the <a href='http://ww2.unime.it/ingegneria/new/index_1024.php'>University of Messina (Italy)</a>, Faculty of Engineering by students enrolled in Master Studies in Computer Engineering and supervised by <a href='http://visilab.unime.it/new/'>Visilab (Computer Vision and Human Computer Interaction Laboratory)</a>.<br>
<br>
<h1><b>Contact us</b></h1>
Davide Mulfari:  davidemulfari@gmail.com<br>
Nicola Peditto:  n.peditto@gmail.com<br>
Carmelo Romeo:   carmelo.romeo85@gmail.com<br>
Fabio Verboso:   fabio.verboso@gmail.com<br>