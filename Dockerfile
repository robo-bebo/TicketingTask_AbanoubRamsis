# Use Ubuntu 22.04 as base
FROM ubuntu:22.04

# Prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    pkg-config \
    libboost-all-dev \
    libssl-dev \
    mosquitto \
    mosquitto-clients \
    libmosquitto-dev \
    xvfb \
    x11-utils \
    libgtk-3-dev \
    libpugixml-dev \
    && rm -rf /var/lib/apt/lists/*


ENV GIT_SSL_NO_VERIFY=1

RUN git clone https://github.com/google/googletest.git /opt/googletest

RUN mkdir -p /opt/googletest/build && cd /opt/googletest/build && \
    cmake .. && \
    make -j$(nproc) && \
    make install

ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Create app directory
WORKDIR /app

# Copy project
COPY ../ /app

# Expose Mosquitto default port
EXPOSE 1883

# Default command (bash shell)
CMD ["/bin/bash"]
