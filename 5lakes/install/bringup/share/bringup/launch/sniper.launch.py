from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer, Node
from launch_ros.descriptions import ComposableNode
from pathlib import Path


def generate_launch_description():
    launch_path = Path(__file__).resolve()
    project_root = launch_path.parents[3]  # 源码运行时: .../Pacific_vision
    if project_root.name == 'bringup' and (project_root / 'share').exists():
        # 安装运行时: .../Pacific_vision/install/bringup/share/bringup/launch/sniper.launch.py
        # parents[3] 会是 .../install/bringup，这里回退到工作区根目录
        project_root = project_root.parents[1]
    
    debug_dump_dir = str(project_root / 'sniper_debug_imgs')  # 调试图片保存目录
    debug_dump_enable = False          # 调试开关：每N帧保存窗口画面
    debug_dump_every_n_frames = 1     # 调试保存间隔(帧)
    dump_save_final = True            # 保存编码端 Final 窗口
    dump_save_decoder = False         # 保存解码端窗口

    # 码率策略（单位：kB/s）
    target_bitrate_kbytes = 12.0       # 目标编码码率
    hard_max_bitrate_kbytes = 14.0     # 传输硬上限（由发送窗口限速实现）
    target_bitrate_kbps = int(target_bitrate_kbytes * 8.0)  # x264 参数单位是 kbps
    # x264_preset = 'veryslow'           # x264 速度预设：slow 会比veryslow更省时延但画质/压缩效率略降
    x264_preset = 'superfast'          # x264 速度预设：ultrafast/superfast/veryfast/faster/fast/medium/slow/slower/veryslow/placebo
    #ultrafast superfast veryfast faster fast medium slow slower veryslow placebo	
    
    
    encode_size = 300

    # 编码端容器（仅编码器；相机由外部 d435i 节点提供）
    encoder_container = ComposableNodeContainer(
        name='sniper_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='doorlock_sniper',
                plugin='doorlock_sniper::VideoEncoderNode',
                name='video_encoder',
                parameters=[
                    {'input_topic': 'image_raw'},   # 输入图像话题（D435i RGB）此处暂为大恒topic
                    {'target_bitrate': target_bitrate_kbps},             # 目标编码码率(kbps)，5kB/s -> 40kbps
                    {'x264_preset': x264_preset},                        # x264 preset: auto/ultrafast/.../veryslow
                    {'output_fps': 25},                                  # 输出帧率原60
                    {'packet_size': 150},                                # 固定分包大小(byte)
                    {'enable_display': False},                           # 关闭编码端显示，避免与解码显示重复
                    {'debug_dump_enable': debug_dump_enable},            # 开启后每N帧保存编码端窗口画面
                    {'debug_dump_every_n_frames': debug_dump_every_n_frames},  # 编码端保存间隔(帧)
                    {'debug_dump_save_final': dump_save_final},          # 编码端 Final 窗口保存开关
                    {'debug_dump_dir': debug_dump_dir},                  # 调试图片根目录
                    {'crop_size': 800},                                  # 中心裁剪ROI大小
                    {'output_size': encode_size},                        # 编码分辨率
                    {'force_monochrome': False},                         # 强制全画面灰度
                    {'bandwidth_limit_kbytes': hard_max_bitrate_kbytes}, # 发送硬上限(kB/s)
                    {'bandwidth_window_s': 0.5},                         # 低延迟优先：缩短限速窗口，原来0.5
                    {'max_tx_delay_s': 0.20}                             # 低延迟优先：严格压缩发送队列时延，原来0.15
                ],
                extra_arguments=[{'use_intra_process_comms': True}]      # 启用进程内零拷贝
            )
        ],
        output='screen',
    )

    # 解码端（Python 节点，独立进程）
    decoder_node = Node(
        package='doorlock_decoder',       # 修正：只保留这一个 package 参数
        executable='decoder_node',        # 对应 setup.py 中的 entry point
        name='video_decoder',
        parameters=[
            {'topic': '/video_stream'},      # 订阅的视频流话题
            {'display': True},               # 显示解码后画面（压缩链路结果）
            {'width': encode_size},                  # 解码期望宽度
            {'height': encode_size},                 # 解码期望高度
            {'display_scale': 1},            # 显示放大倍数(300->600)
            {'debug_dump_enable': debug_dump_enable},            # 开启后每N帧保存解码窗口画面
            {'debug_dump_every_n_frames': debug_dump_every_n_frames},  # 解码端保存间隔(帧)
            {'debug_dump_save_decoder': dump_save_decoder},      # 解码端窗口保存开关
            {'debug_dump_dir': debug_dump_dir}                  # 调试图片根目录
        ],
        output='screen',
        emulate_tty=True,
    )
    udp_forwarder_node = Node(
    package='doorlock_sniper',
    executable='udp_forwarder.py',
    name='udp_forwarder',
    output='screen',
)

    return LaunchDescription([
        encoder_container,
        decoder_node,
        udp_forwarder_node
    ])
