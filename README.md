# &#9786; `openface` - Face detector
This repository is a fork of the [primary repository](https://github.com/ShiqiYu/libfacedetection) with minor modifications to run on Raspian Buster and Ubuntu 18+ with OpenCV. The [Open Horizon](http://github.com/dcmartin/open-horizon) _service_ [`face`](http://github.com/dcmartin/open-horizon/tree/master/face/README.md)  utilizes this repository to build Docker containers.  Please refer to the [Dockerfile](http://github.com/dcmartin/open-horizon/tree/master/face/Dockerfile) for details.

## About
OpenFACE is an open source *face detection* library written in C++.  The library analyzes images and video streams to identify license plates.  The output is the text representation of any license plate characters.

Check out a live online demo here: [http://www.openface.com/demo-image.html](http://www.openface.com/demo-image.html)

## Installation
Outside of use in building the [`face`](http://github.com/dcmartin/open-horizon/tree/master/face/README.md) _service_, see [the original](https://github.com/ShiqiYu/libfacedetection/blob/master/README.md) for instructions.

```
sudo apt update -qq -y && sudo apt install -qq -y git cmake build-essential imagemagick curl jq libopencv-dev
git clone http://github.com/dcmartin/openface.git
cd openface
mkdir build
cd build
cmake ..
make
```

&#9995; Remember to specify **`http://github.com/dcmartin/openface.git`** as the repository.

## Usage
OpenFACE includes a command line utility: `detect-image-demo`. 

## Example
After successfully building the `face` executable  use the shell script [faceanno.sh](example/faceanno.sh) to annotate the original image with all detected license plates, for example:

```
% cd example
% identify people.jpg 
people.jpg JPEG 377x250 377x250+0+0 8-bit sRGB 35090B 0.000u 0:00.000
% ../build/detect-image-demo people.jpg 
{"seconds":0.501369,"count": 23,"results":[{"confidence":99,"x":125,"y":105,"width":26,"height":34,"array":[[134,117],[146,119],[141,125],[133,129],[144,130]]}
,{"confidence":99,"x":300,"y":134,"width":30,"height":36,"array":[[305,150],[317,149],[311,158],[310,162],[321,160]]}
,{"confidence":99,"x":84,"y":80,"width":23,"height":29,"array":[[91,91],[101,91],[96,96],[92,101],[101,100]]}
,{"confidence":99,"x":318,"y":82,"width":25,"height":32,"array":[[324,95],[336,95],[330,101],[325,106],[335,106]]}
,{"confidence":99,"x":220,"y":33,"width":21,"height":27,"array":[[228,43],[236,43],[232,49],[228,53],[235,53]]}
,{"confidence":99,"x":129,"y":31,"width":22,"height":28,"array":[[135,42],[143,41],[139,47],[136,52],[144,51]]}
,{"confidence":99,"x":62,"y":110,"width":29,"height":37,"array":[[73,125],[86,124],[81,133],[73,138],[84,137]]}
,{"confidence":99,"x":69,"y":26,"width":19,"height":24,"array":[[74,36],[83,35],[78,40],[75,44],[83,43]]}
,{"confidence":99,"x":340,"y":66,"width":21,"height":26,"array":[[346,76],[356,77],[351,81],[346,85],[355,86]]}
,{"confidence":99,"x":204,"y":65,"width":24,"height":32,"array":[[213,78],[224,79],[218,85],[211,88],[221,89]]}
,{"confidence":99,"x":265,"y":63,"width":24,"height":31,"array":[[273,76],[283,76],[279,82],[274,86],[283,86]]}
,{"confidence":99,"x":33,"y":47,"width":23,"height":27,"array":[[39,59],[49,58],[44,64],[40,68],[49,67]]}
,{"confidence":99,"x":91,"y":183,"width":23,"height":30,"array":[[97,197],[107,195],[102,203],[100,207],[108,206]]}
,{"confidence":99,"x":146,"y":164,"width":31,"height":37,"array":[[157,178],[170,183],[161,188],[152,190],[163,194]]}
,{"confidence":99,"x":240,"y":100,"width":33,"height":39,"array":[[247,120],[259,115],[253,126],[253,130],[264,126]]}
,{"confidence":98,"x":92,"y":54,"width":19,"height":24,"array":[[100,65],[108,64],[105,69],[100,73],[107,73]]}
,{"confidence":97,"x":18,"y":88,"width":29,"height":35,"array":[[25,105],[37,101],[32,111],[29,117],[39,114]]}
,{"confidence":96,"x":284,"y":46,"width":17,"height":20,"array":[[288,53],[295,53],[291,58],[289,60],[294,61]]}
,{"confidence":94,"x":319,"y":48,"width":21,"height":24,"array":[[324,56],[332,57],[327,61],[324,65],[331,66]]}
,{"confidence":92,"x":150,"y":68,"width":24,"height":29,"array":[[158,78],[168,81],[162,85],[156,89],[164,91]]}
,{"confidence":91,"x":221,"y":174,"width":27,"height":35,"array":[[231,188],[244,187],[239,194],[233,200],[243,200]]}
,{"confidence":82,"x":158,"y":40,"width":23,"height":27,"array":[[165,51],[174,52],[169,57],[164,60],[171,61]]}
,{"confidence":62,"x":172,"y":108,"width":27,"height":33,"array":[[177,124],[186,122],[181,130],[183,135],[189,133]]}
]}
```

# `faceanno.sh` script

The script requires [ImageMagick](https://imagemagick.org/index.php) and [`jq`](https://stedolan.github.io/jq/) software; to install on Debian LINUX: 

```
sudo apt update -qq -y && sudo apt install -qq -y imagemagick jq
```

Use the the shell script to annotate the image; for example:

```
% cd example
% ../build/detect-image-demo people.jpg > people.json
% ./faceanno.sh people
people-face.jpg
```


### Output
![](example/people-face.jpg?raw=true "EA7THE")

# Changelog & Releases

Releases are based on Semantic Versioning, and use the format
of ``MAJOR.MINOR.PATCH``. In a nutshell, the version will be incremented
based on the following:

- ``MAJOR``: Incompatible or major changes.
- ``MINOR``: Backwards-compatible new features and enhancements.
- ``PATCH``: Backwards-compatible bugfixes and package updates.

# Authors & contributors

David C Martin (github@dcmartin.com)
