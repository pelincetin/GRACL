# Based on 20.04 LTS
FROM ubuntu:focal

ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get -yq update && \
    apt-get -y upgrade && \
    apt-get -yq --no-install-suggests --no-install-recommends install \
    ocaml \
    menhir \
    llvm-10 \
    llvm-10-dev \
    m4 \
    git \
    aspcud \
    ca-certificates \
    python2.7 \
    pkg-config \
    cmake \
    opam \
    clang \
    valgrind

RUN ln -s /usr/bin/lli-10 /usr/bin/lli
RUN ln -s /usr/bin/llc-10 /usr/bin/llc

RUN opam init 
RUN opam install --disable-sandboxing \ 
    llvm.10.0.0 \ 
    ocamlfind 

WORKDIR /root

ENTRYPOINT ["opam", "config", "exec", "--"]

CMD ["bash"]