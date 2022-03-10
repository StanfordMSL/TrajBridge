#include <bridge_iroad/udp_server.h>

UDP_Server::UDP_Server()
{
  int sockfd;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr, cliaddr;
  
  struct iroad_cmd cmd_struct;

  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if (bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  socklen_t len;
  int n;

  len = sizeof(cliaddr); //len is value/result
  
  n = recvfrom(sockfd, &cmd_struct, sizeof(cmd_struct), MSG_WAITALL, (struct sockaddr *)&cliaddr,&len);
  printf("Steer: %f\n",cmd_struct.steer);
  printf("Ct_Input: %f\n",cmd_struct.ct_input);
  printf("Accel: %f\n",cmd_struct.accel);
  printf("Pk_Brake: %f\n",cmd_struct.pk_brake);
  printf("PRNDL_vr: %f\n",cmd_struct.PRNDL_vr);
  printf("PRNDL_ct: %f\n",cmd_struct.PRNDL_ct);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "UDP_Server");
  UDP_Server UDP_Server;

  ros::spin();
  return 0;
}
