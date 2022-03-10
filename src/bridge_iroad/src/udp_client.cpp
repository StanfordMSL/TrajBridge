#include <bridge_iroad/udp_client.h>

UDP_Client::UDP_Client()
{
  int sockfd;
  char buffer[MAXLINE];

  struct iroad_cmd cmd_struct;

  cmd_struct.steer = 1.0;
  cmd_struct.ct_input = 2.0;
  cmd_struct.accel = 3.0;
  cmd_struct.pk_brake = 4.0;
  cmd_struct.PRNDL_vr = 5.0;
  cmd_struct.PRNDL_ct = 6.0;
  
  struct sockaddr_in servaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  socklen_t len;
  int n;

  sendto(sockfd, &cmd_struct, sizeof(cmd_struct),MSG_CONFIRM, (const struct sockaddr *)&servaddr,sizeof(servaddr));
  close(sockfd);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "UDP_Client");
  UDP_Client UDP_Client;

  ros::spin();
  return 0;
}
