# Test Source

## 구성

    ─┬ sorc_test
      ├─ comm_cpp               # c++ 공통 소스 라이브러리
      ├─ doc                    # 문서
      ├─ include                # c/c++ Header
      ├─ lib                    # c/c++ Library
      ├─ perl                   # Perl Script
      ├─ shell                  # Shell Script
      └┬ src
        ├─ DB                       # DB
        │  ├─ mysql                    # myqql - c library 소스
        │  └─ pqxx                     # PostgreSQL - libpqxx library 소스
        ├─ JSON                     # JSON
        │  ├─ jsoncpp                  # jsoncpp library 소스
        │  └─ rapidjson                # rapidjson library 소스
        ├─ c                        # c 소스
        ├─ cpp                      # c++ 소스
        ├─ msgque                   # Message Queue 소스
        ├─ net                      # 네트워크 소스
        ├─ openssl                  # openssl 소스
        │  └─ ssl                      # ssl 소스
        ├─ random                   # 난수 소스
        └─ spdlog                   # spdlog library 소스

