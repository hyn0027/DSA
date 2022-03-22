echo "Start checking"
function getTiming(){ 
    start=$1
    end=$2  
    start_s=$(echo $start | cut -d '.' -f 1)
    start_ns=$(echo $start | cut -d '.' -f 2)
    end_s=$(echo $end | cut -d '.' -f 1)
    end_ns=$(echo $end | cut -d '.' -f 2)
    time=$(( ( 10#$end_s - 10#$start_s ) * 1000 + ( 10#$end_ns / 1000000 - 10#$start_ns / 1000000 ) ))
    echo "$time ms"
} 


for data_source in 0 1
do
    for query_type in 0 1 2
    do
        ./data $data_source $query_type > data.in
        for hashing_strategy in 0 1 2
        do
            for collision_strategy in 0 1 2
            do
                start=$(date +%s.%N)
                timeout 20 ./main $hashing_strategy $collision_strategy < data.in > test.out
                end=$(date +%s.%N)
                result=$(getTiming $start $end) 
                echo $data_source $query_type $hashing_strategy $collision_strategy: $result
            done
        done  
    done
done