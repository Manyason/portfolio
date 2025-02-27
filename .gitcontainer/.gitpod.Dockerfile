FROM gitpod/workspace-full  

# 必要なパッケージをインストール
RUN sudo apt update && sudo apt install -y \
    mininet \
    python3-pip \
    git

# Ryu SDN Controllerをインストール
RUN pip3 install ryu

# 作業ディレクトリを設定
WORKDIR /workspace