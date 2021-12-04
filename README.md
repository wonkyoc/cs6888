How to run
==========

# Build docker
```
$ ./setup.sh
```

# Run docker
```
$ docker images | head -n2 | tail -n1 | awk -F " " '{print $3}'
<Docker image ID> # e.g., abcd

$ docker run --rm -ti --ulimit='stack=-1:-1' abcd
```

# Run test
```
klee@<container_id>:~$ pwd
/home/klee
klee@<container_id>:~$ ./run.sh
```

