# Linux

## 시스템

    $ grep /etc/os-release                                             # version

    $ hostnamectl set-hostname <new_hostname>                          # 호스트명 변경

## 계정

### 그룹

    $ groupadd <group_name> -g <gid>                                   # 그룹 생성

    $ groupmod -n <old_group> <new_group>                              # 그룹명 변경


### 사용자

    $ useradd -u <uid> -g <gid> -d <path> -G wheel <account>           # 계정 생성

    $ usermod -g <group> <account>                                     # primary 그룹 변경
    $ usermod -G <group> <account>                                     # secondary 그룹 변경
    $ usermod -G <group> -a <account>                                  # 그룹 추가

    $ userdel <account>                                                # 계정 삭제
    
    $ chage -l <account>                                               # 계정상태보기
    $ chage -E -1 <account>                                            # 계정만료 해제
    $ chage -M -1 <account>                                            # 암호만료 해제

    $ echo '<account>:<password>' | chpasswd                           # 암호 변경

## Network

    $ hostname -i                                                      # ip 확인

    $ netstat -nltp | grep <port>                                      # port 사용중인 프로세스

    $ scp <source> [account@]<target_server>:<target_folder>           # 파일전송 (scp)	

## Disk

    $ fdisk -l

## 파일

| 파일 | 내용 |
| ---- | ---- |
| /etc/group | 그룹 |
| /etc/password | 계정 |
| /etc/profile.d/bash_history.sh | bash 히스토리 설정 |


