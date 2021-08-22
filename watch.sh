# ps -x --forest | grep "a\.out"
# pstree -p | grep "a.out"
pstree | grep "a.out" | sed -E "s/(.*)(a\.out)/\2/"