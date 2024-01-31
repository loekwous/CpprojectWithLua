# Use the official Ubuntu 22.04 base image
FROM ubuntu:22.04 as base

ARG USER_AND_GROUP_ID=1001
ARG USER_AND_GROUPNAME=luauser

USER root

# Install build-essential for build utilities and cmake
RUN apt-get update \
    && apt install -y git build-essential cmake ninja-build libreadline-dev sudo \
    && rm -rf /var/lib/apt/lists/*

# Add a user with sudo permissions
RUN groupadd -f --gid ${USER_AND_GROUP_ID} ${USER_AND_GROUPNAME} && \
    id -u somename &>/dev/null || useradd --create-home --uid ${USER_AND_GROUP_ID} --gid ${USER_AND_GROUP_ID} -G plugdev,dialout --shell /bin/bash -m ${USER_AND_GROUPNAME} && \
    echo "${USER_AND_GROUPNAME} ALL=(ALL:ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USER_AND_GROUPNAME}

# Include metadata for usage as a devcontainer
LABEL devcontainer.metadata="[{ \
  \"privileged\": true, \
  \"overrideCommand\": false, \
  \"remoteUser\": \"${USER_AND_GROUPNAME}\", \
  \"containerEnv\": { \"WAYLAND_DISPLAY\": \"disabled-by-inspiro-dockerfile\" }\
}]"

USER ${USER_AND_GROUPNAME}