cat ip_filter.tsv | ip_filter > output.txt
echo "24e7a7b2270daee89c64d3ca5fb3da1a  output.txt" | md5sum -c -
