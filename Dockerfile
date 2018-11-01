FROM centos:7

WORKDIR /

RUN yum -y update && \
    yum -y install git gcc make wget

RUN wget http://www.mpich.org/static/downloads/3.1.4/mpich-3.1.4.tar.gz && \
    tar -xzf mpich-3.1.4.tar.gz && \
    mkdir /mpich3

RUN pushd mpich-3.1.4 && \
    ./configure --prefix=/mpich3 --disable-fortran --disable-cxx && \
    make && \
    make install && \
    popd

RUN echo 'export PATH="/mpich3/bin:$PATH"' >> /root/.bashrc && \
    echo 'export LD_LIBRARY_PATH="/mpich3/lib:$LD_LIBRARY_PATH"' >> /root/.bashrc && \
    rm -f /root/anaconda-ks.cfg

WORKDIR /root

CMD [ "/bin/bash" ]
