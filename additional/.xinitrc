#!/bin/sh
#####################
# ~/.xinitrc for:   #
# DWM Aram1d Config #
#####################

# source xinitc.d scripts
if [ -d /etc/X11/xinit/xinitrc.d ]; then
  for f in /etc/X11/xinit/xinitrc.d/*; do
    [ -x "$f" ] && . "$f"
  done
  unset f
fi

# load .Xresources
[[ -f $HOME/.Xresources ]] && xrdb -merge $HOME/.Xresources

# remap caps lock to control, remap right alt to window key
#setxkbmap -option ctrl:nocaps
#xmodmap -e "keycode 108 = Super_L"
#xmodmap -e "remove mod1 = Super_L"

# add font paths
xset fp default
[[ -d /usr/share/fonts/local ]] && xset +fp /usr/share/fonts/local
[[ -d /usr/share/fonts/OTF ]] && xset +fp /usr/share/fonts/OTF
[[ -d $HOME/.local/share/fonts ]] && xset +fp $HOME/.local/share/fonts
xset fp rehash

numlockx &

# turn monitor off after 60min
xset s off
xset dpms 3600 3600 3600

# increase mouse acceleration
xset m 3

# set WM to a name with Java recognises
#wmname LG3D
export _JAVA_AWT_WM_NONREPARENTING=1

# set background
sh $HOME/.fehbg

#set transparency
xcompmgr -c &

# start WM and status bar, which is reloaded every second
while true; do 
/usr/bin/dwm-status
sleep 1s
done &
exec dwm
