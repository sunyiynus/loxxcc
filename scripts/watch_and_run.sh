#!/bin/bash

# 定义要监视的目录，这里假设是当前目录
WATCH_DIR="./.."

# 定义你的 make 命令和 run 命令
MAKE_CMD="cmake --build ."
RUN_CMD="./my_program"  # 替换成你的运行命令

echo "Watching for changes in $WATCH_DIR..."

# 使用 inotifywait 监视目录变化
while true; do
    # 等待文件变动（修改、创建、删除等）
    inotifywait -r -e modify,create,delete $WATCH_DIR

    # 文件变动时执行 make 和 run 命令
    echo "Changes detected. Running make..."
    $MAKE_CMD

    # 如果 make 成功，执行 run 命令
    if [ $? -eq 0 ]; then
        echo "Running program..."
        $RUN_CMD
    else
        echo "Make failed, skipping run."
    fi
done
