import open3d as o3d
import os 

pcd_data_dir = "../Data/points/"
pcd_file = "000035.pcd"
pcd_dir = os.path.join(pcd_data_dir, pcd_file)

pcd = o3d.io.read_point_cloud(pcd_dir)
print(pcd)
o3d.visualization.draw_geometries([pcd])