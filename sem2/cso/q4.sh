#sudo su&
#tmux start-server
tmux new-session -d -s mysession
#tmux send-keys -t mysession 'htop'
tmux splitw -v -t mysession
tmux send-keys -t mysession 'sudo tcpdump -v port 80 or port 443' C-m
tmux select-pane -U
tmux splitw -h -t mysession
tmux send-keys -t mysession 'watch -n1 "date +%T|figlet -W -f big"' C-m
tmux select-pane -L
tmux send-keys -t mysession 'htop' C-m
tmux select-pane -D
tmux attach -t mysession
#htop

