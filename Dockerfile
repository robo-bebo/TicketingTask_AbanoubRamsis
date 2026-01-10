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
    pugixml-dev \
    && rm -rf /var/lib/apt/lists/*

# Create app directory
WORKDIR /app

# Copy project
COPY ../ /app

# Expose Mosquitto default port
EXPOSE 1883

# Default command (bash shell)
CMD ["/bin/bash"]
