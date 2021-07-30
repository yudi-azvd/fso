#!/bin/bash

# Seria interessante se esse script já executasse o programa

main() {
  test_cases=(
    "SIGUSR1 SIGALRM SIGALRM SIGALRM"
    "SIGUSR1 SIGALRM SIGALRM SIGUSR1 SIGALRM"
  )

  test_case_index=$1
  program_name="a"

  if [ "$1" == "-d" ]; then # debug
    echo "debug"
    # no futuro, pegar esse nome automaticamente com ./$0.sh
    program_name="secreto"
  fi
  
  pid=$(find_process_pid $program_name)

  regex_for_number='^[0-9]+$'
  if ! [[ $pid =~ $regex_for_number ]]; then
    echo "did not find $program_name($pid)"
    exit 1;
  fi

  if [ -z "$1" ] || [ $1 == "-d" ] ; then
    echo "found $program_name($pid)" >&2 # nao vai pra saida padrao
    echo -n $pid | xclip -selection clipboard # -n remove o '\n'
    echo "$program_name PID '$pid' copied to clipboard" >&2
    exit 1;
  fi

  send_signals_to_process pid

  echo "found PID $pid" >&2 # nao vai pra saida padrao
  echo -n $pid | xclip -selection clipboard # -n remove o '\n'
  echo "process PID '$pid' copied to clipboard" >&2
}


#################################
#################################
#################################

find_process_pid() {
  program_name=$1 # achei que deveria ser $0
  pid=$(pstree yudi -p | grep $program_name.out | sed -E "s/^(.+)$program_name\.out\(([0-9]+)\)/\2/")
  echo "$pid"
}

send_signals_to_process() {
  proc_pid=$0

  for sig in ${test_cases[test_case_index]}; do
    echo "sent $sig" >&2
    kill -s ${sig} ${pid}
    sleep 0.001 # a.out dá segfault se não tem sleep
  done
}

# passa os argumentos de linha de commando para main()
main "$@"


