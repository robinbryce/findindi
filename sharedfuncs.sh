really_install_path=/usr/sbin/really

choose_privilege_escalate() {
    if [ -f "$really_install_path" ]; then
        echo "$really_install_path"
    else
        which_really=$(which really)
        if [ "" = "$which_really" ]; then
            echo "sudo"
        else
            echo "$which_really"
        fi
    fi
    # TODO: ssh root@localhost (assuming passwordless key or ssh-add'd)
}

