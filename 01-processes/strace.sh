# Rastreia os sinais recebidos por um processo
# https://unix.stackexchange.com/questions/186200/whats-the-easiest-way-to-detect-what-signals-are-being-sent-to-a-process
echo "arguments to $0:" $@

strace -p $1 -e 'trace=!all'

