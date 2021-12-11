# Prerequisite
## Update sub repo
```
$ git submodule init
$ git submodule update
```


After processing the prerequisite, you should follow either way to setup the system. We highly recommend that docker setup is the easiest way to do.

# Docker setup
## Build docker
You must have the docker engine in the system. If you do not have the docker,
you should follow the [guideline](https://docs.docker.com/engine/install/ubuntu/). 
If you already have, then type the command below which will automatically create a docker image file and copy scripts into docker system.
```
$ ./setup.sh
```

Note that docker needs the root user. If you use non-root user, then you should follow
[this guideline](https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user).

## Run docker
The command is basically to get the docker image file ID and run its container. 
```
$ docker images | head -n2 | tail -n1 | awk -F " " '{print $3}'
<docker image ID> # e.g., abcd

$ docker run --rm -ti --ulimit='stack=-1:-1' <docker image ID>
```

## Run test
This command works in the docker, not the host system.
```
klee@<container_id>:~$ pwd
/home/klee
klee@<container_id>:~$ ./run.sh
```

# Non-docker setup
This step is quite complicated and requires a lot of builds. We recommend that you use
the docker engine for one-click build. The core part is to build each submodule as instruction says.

## Build customized hiredis
```
$ cd hiredis
$ make
$ ls | grep libhiredis.a
libhiredis.a
$ ls | grep test.bc
test.bc
```
You should see that there are `test.bc` and `libhiredis.a` under the parent directory.

## Build Redis
```
$ sudo apt install wget
$ wget https://download.redis.io/releases/redis-6.2.6.tar.gz
$ tar -xvzf redis-6.2.6.tar.gz
$ cd redis-6.2.6
$ make
```

To run the server application as a background process, execute `$ ./redis-6.2.6/src/redis-server --daemonize yes`.
To kill this process, type `$ pkill redis-server`. Note that this server should be alive while the testing is running.


## Build customized KLEE
Every setup is the same with [the official guideline](https://klee.github.io/build-llvm9/) except for building KLEE with `cmake`.
For our setup, you need to enable `hiredis` and configure its path. We only include the cmake configuration. 
We add `-DENABLE_REDIS=ON` and `-DREDIS_PATH=<HIREDIS_SRC_DIR>`. You should install contraint solver and other libraries offered by KLEE to 
make the correct environment.

```
$ cd klee
$ cmake \
  -DENABLE_SOLVER_STP=ON \
  -DENABLE_POSIX_RUNTIME=ON \
  -DENABLE_KLEE_UCLIBC=ON \
  -DENABLE_REDIS=ON \ 
  -DKLEE_UCLIBC_PATH=<KLEE_UCLIBC_SOURCE_DIR> \
  -DREDIS_PATH=<HIREDIS_SRC_DIR> \
  -DLLVM_CONFIG_BINARY=<PATH_TO_llvm-config-9> \
  -DLLVMCC=<PATH_TO_clang-9> \
  -DLLVMCXX=<PATH_TO_clang++-9> \
  <KLEE_SRC_DIRECTORY>
```

If you need to use KLEE in your local path, you should execute this command.
```
# Add klee path into bash
$ echo "PATH=$PATH:/path/to/custom-klee/build/bin:" >> ~/.bashrc

# Check the command works
$ klee --version
klee 2.3-pre
```

## Run test
Finally, if everything is working then we are able to test an application.

```
$ pwd
/path/to/cs6888

$ cd hiredis
$ klee --redis --libc=uclibc --posix-runtime test.bc
...
Test completed...
...

```

