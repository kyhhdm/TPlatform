./shutdown.sh

for (( i=0 ; $i < ${#WORKER_HOSTS[*]} ; i++ ))
do
  echo "======== ${WORKER_HOSTS[$i]} ========"
  ssh ${USERNAME}@${WORKER_HOSTS[$i]} "rm -rf ${WORKER_DATA_DIR}/*"
done

./startup.sh
