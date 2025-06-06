FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    python3 \
    python3-pip \
    python3-venv \
    git \
    libgl1-mesa-dev \
    libcurl4-openssl-dev \
    libssl-dev \
    nlohmann-json3-dev \
    x11vnc \
    xvfb \
    fluxbox \
    libwayland-client0 \
    libxkbcommon0 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY requirements.txt .
RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

RUN chmod +x /app/entrypoint.sh

RUN mkdir -p build && cd build && \
    cmake .. && \
    make

ENTRYPOINT ["/app/entrypoint.sh"]