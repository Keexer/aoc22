FROM	alpine

LABEL	author="Jacob"

WORKDIR /home/AoC

# Copy source and get correct dependencies
COPY	./Input ./Input
COPY	./build/linux/App ./app/store/App
RUN		apk update
RUN		apk add libstdc++
RUN		apk add libc6-compat
RUN		apk add libgcc
#RUN		apk add cmake
#RUN		apk add g++
#RUN		apk add make

# Build application
#RUN		cmake -B/home/AoC/build/linux -DCMAKE_BUILD_TYPE=Release
#RUN		cmake --build /home/AoC/build/linux

# Remove source code
#RUN		mkdir -p ../bin/store/app
#RUN		cp App ../bin/store/app/
#RUN		cp build/linux/App ../bin/store/app/
#RUN		cp -r Input ../bin/Input
#WORKDIR /home
#RUN		rm -r AoC

# Remove dependencies
#RUN		apk del cmake
#RUN		apk del make

WORKDIR /home/AoC/app/store/

ENTRYPOINT ["./App"]