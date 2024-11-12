
import sys
import os
from graphviz import Source

def render_dot_files_in_directory(directory_path):
    # 检查目录是否存在
    if not os.path.isdir(directory_path):
        print(f"Error: Directory {directory_path} does not exist.")
        return

    # 遍历目录中的所有文件
    for filename in os.listdir(directory_path):
        if filename.endswith(".dot"):
            # 构建文件的完整路径
            file_path = os.path.join(directory_path, filename)
            # 读取并渲染 .dot 文件
            with open(file_path, 'r') as f:
                dot_source = f.read()
            graph = Source(dot_source)
            # 保存为 PNG 文件，使用相同的文件名
            output_file = os.path.join(directory_path, filename.rsplit('.', 1)[0])
            graph.render(output_file, format='png', cleanup=True)
            print(f"Rendered {filename} to {output_file}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python render_dot.py <dot_file_path>")
    else:
        render_dot_files_in_directory(sys.argv[1])