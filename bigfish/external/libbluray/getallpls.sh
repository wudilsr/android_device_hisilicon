for pls in `ls /home/public/zhangyi/iso/TRANSFORMERS3D/BDMV/PLAYLIST/`;
do
./src/examples/mpls_dump -vlp /home/public/zhangyi/iso/TRANSFORMERS3D/BDMV/PLAYLIST/$pls >> result.txt;
done;
