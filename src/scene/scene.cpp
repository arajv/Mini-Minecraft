#include <scene/scene.h>
#include <scene/cube.h>

Scene::Scene() : dimensions(64, 64, 64)
{
//    for(int x = -64; x < 600; x++)
//    {
//        for(int z = -64; z < 600; z++)
//        {
//            noise2D[make_tuple(x,z)] =  PerlinNoise_2D(x, z);
//        }
//    }

}


void Scene::CreateTestScene()
{
//    unordered_map<tuple<int,int,int>,int> temp;
//    newchunks = temp;
    unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> > mChunk;
    chunks = mChunk;
    for(int x = 0; x < dimensions.x; x++)
    {
        for(int z = 0; z < dimensions.z; z++)
        {
            //objects[make_tuple(x,dimensions.y/2,z)] = green;
            tuple<int,int,int> chunk_coord;
            get<0>(chunk_coord) = int(floor(x/16.0));
            get<1>(chunk_coord) = int(floor(dimensions.y/32.0));
            get<2>(chunk_coord) = int(floor(z/16.0));
            //float decide = PerlinNoise_1Dnew(x*x+z*z);
            if (color.find(make_tuple(x,dimensions.y/2,z))!=color.end()){
               // chunks[chunk_coord][make_tuple(x,dimensions.y/2,z)] = color[make_tuple(x,dimensions.y/2,z)];
            }
            else{
                chunks[chunk_coord][make_tuple(x,dimensions.y/2,z)] = dirt;
            }


            //newchunks[chunk_coord] = 1;
                //allchunks[chunk_coord][make_tuple(x,dimensions.y/2,z)] = green;

            //else{
                // Retaining the old block
                //chunks[chunk_coord][make_tuple(x,dimensions.y/2,z)] = allchunks[chunk_coord][make_tuple(x,dimensions.y/2,z)];
            //}
            int hn;
            if (height.find(make_tuple(x,z))!=height.end()){
                hn = height[make_tuple(x,z)];
            }
            else{
                hn = 3+round(9*PerlinNoise_2D(x, z));
            }
            //height = round(hn);


            for (int y = 1; y <= hn; y++){
                //objects[make_tuple(x,y+dimensions.y/2,z)] = green;
                get<1>(chunk_coord) = int(floor((y+dimensions.y/2)/16.0));

                if (color.find(make_tuple(x,dimensions.y/2,z))!=color.end()){
                    //chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = color[make_tuple(x,dimensions.y/2,z)];
                }
                else{
                    if (y== hn){
                        chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = green;
                    }
                    else{
                        chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = dirt;
                    }
                }

            }

        }

    }
}

void Scene::modify_scene(tuple<int,int,int> centre){
    //map< tuple<int,int,int>, int> newmap;
    //objects = newmap;
    unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> > mChunk;
    chunks = mChunk;
//    unordered_map<tuple<int,int,int>,int> temp;
//    newchunks = temp;
    int minx = get<0>(centre) - dimensions.x/2;
    int maxx = get<0>(centre) + dimensions.x/2;
    int minz = get<2>(centre) - dimensions.z/2;
    int maxz = get<2>(centre) + dimensions.z/2;
    for(int x = minx; x < maxx; x++)
    {
        for(int z = minz; z < maxz; z++)
        {



            //objects[make_tuple(x,dimensions.y/2,z)] = green;
            tuple<int,int,int> chunk_coord;
            get<0>(chunk_coord) = int(floor(x/16.0));
            get<1>(chunk_coord) = int(floor(dimensions.y/32.0));
            get<2>(chunk_coord) = int(floor(z/16.0));
            //float decide = PerlinNoise_1Dnew(x*x+z*z);
            if (color.find(make_tuple(x,dimensions.y/2,z))!=color.end()){
                //chunks[chunk_coord][make_tuple(x,dimensions.y/2,z)] = color[make_tuple(x,dimensions.y/2,z)];
            }
            else{                
                chunks[chunk_coord][make_tuple(x,dimensions.y/2,z)] = dirt;
            }


            int hn;
            if (height.find(make_tuple(x,z))!=height.end()){
                hn = height[make_tuple(x,z)];
            }
            else{
                hn = 3+round(9*PerlinNoise_2D(x, z));
            }

            for (int y = 1; y <= hn; y++){

                get<1>(chunk_coord) = int(floor((y+dimensions.y/2)/16.0));
                if (color.find(make_tuple(x,dimensions.y/2,z))!=color.end()){
                    //chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = color[make_tuple(x,dimensions.y/2,z)];
                }
                else{
                    if (y== hn){
                        chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = green;
                    }
                    else{
                        chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = dirt;
                    }
                }

            }

        }
    }
}

void Scene::make_caves(tuple<int,int,int> centre){

    unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> > mChunk;
    chunks = mChunk;
    unordered_map<tuple<int,int,int>,int> temp;
    newchunks = temp;
    int mix = get<0>(centre) - dimensions.x/2;
    int max = get<0>(centre) + dimensions.x/2;
    int miz = get<2>(centre) - dimensions.z/2;
    int maz = get<2>(centre) + dimensions.z/2;
    int lowest = -31;


    for(int x = mix; x < max; x++)
    {
        for(int z = miz; z < maz; z++)
        {
            int y = lowest-1;
            tuple<int,int,int> chunk_coord;
            get<0>(chunk_coord) = int(floor(x/16.0));
            get<1>(chunk_coord) = int(floor(y/16.0));
            get<2>(chunk_coord) = int(floor(z/16.0));
            chunks[chunk_coord][make_tuple(x,y,z)] = bedrock;
            //newchunks[chunk_coord] = 1;
            allchunks[make_tuple(x,y,z)] = bedrock;

        }
    }

    // Cave Creation
    int startx = mix+round(63*PerlinNoise_1D(get<0>(centre)));
    int startz = miz+round(63*PerlinNoise_1D(get<2>(centre)));
    int starty = 15;
    int currx = startx, curry = starty, currz = startz;
    int minx, maxx, miny, maxy, minz, maxz;
    int radius = 5;
    int step = 2;
    int count = 0;
    int numiter = 40;
    int ellipsoid = 10+int(round((numiter-10)*PerlinNoise_2D(get<0>(centre),get<2>(centre))));

    srand (time(NULL));

    while(true){
        /*
        if (count==0){
            for (int x = currx-4; x<=currx+4; x++){
                for (int y = curry+1; y<=curry+17; y++){
                    for (int z = currz-4; z<=currz+4; z++){
                        tuple<int,int,int> chunk_coord;
                        get<0>(chunk_coord) = int(floor(x/16.0));
                        get<1>(chunk_coord) = int(floor(y/16.0));
                        get<2>(chunk_coord) = int(floor(z/16.0));
                        if (x==currx-4 || x==currx+4 || z==currz-4 || z==currz+4){
                            chunks[chunk_coord][make_tuple(x,y,z)] = coal;
                            //newchunks[chunk_coord] = 1;
                            allchunks[chunk_coord][make_tuple(x,y,z)] = coal;
                        }
                        else{
                            chunks[chunk_coord][make_tuple(x,y,z)] = empty;
                            //newchunks[chunk_coord] = 1;
                            allchunks[chunk_coord][make_tuple(x,y,z)] = empty;
                        }
                    }
                }
            }
        }
        */
        if (count== ellipsoid){
            int radiusx = rand() % 3 + 9;
            int radiusy = rand() % 2 + 5;
            int radiusz = rand() % 3 + 8;
            minx = currx - radiusx-3;
            maxx = currx + radiusx+3;
            miny = curry - radiusy-3;
            maxy = curry + radiusy+3;
            minz = currz - radiusz-3;
            maxz = currz + radiusz+3;
            for (int x = minx; x<=maxx; x++){
                for (int y = miny; y<=maxy; y++){
                    for (int z = minz; z<=maxz; z++){
                        float dist2 = (x-currx)*(x-currx)/float(radiusx*radiusx) +
                                (y-curry)*(y-curry)/float(radiusy*radiusy)+(z-currz)*(z-currz)/float(radiusz*radiusz);
                        if (dist2<=1 && y>=lowest && y<=starty){
                            tuple<int,int,int> chunk_coord;
                            get<0>(chunk_coord) = int(floor(x/16.0));
                            get<1>(chunk_coord) = int(floor(y/16.0));
                            get<2>(chunk_coord) = int(floor(z/16.0));
                            chunks[chunk_coord][make_tuple(x,y,z)] = empty;
                            //newchunks[chunk_coord] = 1;
                            allchunks[make_tuple(x,y,z)] = empty;
                        }
                        if (dist2 > 1 && dist2 < 3 && y>=lowest && y<=starty){
                            tuple<int,int,int> chunk_coord;
                            get<0>(chunk_coord) = int(floor(x/16.0));
                            get<1>(chunk_coord) = int(floor(y/16.0));
                            get<2>(chunk_coord) = int(floor(z/16.0));
                            if (allchunks[make_tuple(x,y,z)]!=empty && y<= 3+miny+0.1*2*radiusy){
                                chunks[chunk_coord][make_tuple(x,y,z)] = lava;
                                //newchunks[chunk_coord] = 1;
                                allchunks[make_tuple(x,y,z)] = lava;
                            }
                            else if (allchunks[make_tuple(x,y,z)]!=empty && y> 3+miny+0.1*2*radiusy){
                                int coaloriron = rand()%3;
                                if (coaloriron==0){
                                    chunks[chunk_coord][make_tuple(x,y,z)] = coal;
                                    //newchunks[chunk_coord] = 1;
                                    allchunks[make_tuple(x,y,z)] = coal;
                                }
                                else if (coaloriron==1){
                                    chunks[chunk_coord][make_tuple(x,y,z)] = iron_ore;
                                    //newchunks[chunk_coord] = 1;
                                    allchunks[make_tuple(x,y,z)] = iron_ore;
                                }
                            }
                            else {
                                // Retaining the old block
                                chunks[chunk_coord][make_tuple(x,y,z)] = allchunks[make_tuple(x,y,z)];
                            }
                        }

                    }
                }
            }

        }
        else{
            minx = currx - radius;
            maxx = currx + radius;
            miny = curry - radius;
            maxy = curry + radius;
            minz = currz - radius;
            maxz = currz + radius;

            for (int x = minx; x<=maxx; x++){
                for (int y = miny; y<=maxy; y++){
                    for (int z = minz; z<=maxz; z++){
                        int dist2 = (x-currx)*(x-currx)+(y-curry)*(y-curry)+(z-currz)*(z-currz);

                        if ( dist2 < (radius-1)*(radius-1) && y>=lowest && y<=starty){
                            tuple<int,int,int> chunk_coord;
                            get<0>(chunk_coord) = int(floor(x/16.0));
                            get<1>(chunk_coord) = int(floor(y/16.0));
                            get<2>(chunk_coord) = int(floor(z/16.0));
                            chunks[chunk_coord][make_tuple(x,y,z)] = empty;
                            //newchunks[chunk_coord] = 1;
                            allchunks[make_tuple(x,y,z)] = empty;
                        }
                        if (dist2 >= (radius-1)*(radius-1)&& dist2 <= (radius+1)*(radius+1)&& y>=lowest && y<=starty){
                            tuple<int,int,int> chunk_coord;
                            get<0>(chunk_coord) = int(floor(x/16.0));
                            get<1>(chunk_coord) = int(floor(y/16.0));
                            get<2>(chunk_coord) = int(floor(z/16.0));

                            if (allchunks[make_tuple(x,y,z)]!=-1 && allchunks[make_tuple(x,y,z)]!=10){
                                int coaloriron = rand()%3;
                                if (coaloriron==0){
                                    chunks[chunk_coord][make_tuple(x,y,z)] = coal;
                                    //newchunks[chunk_coord] = 1;
                                    allchunks[make_tuple(x,y,z)] = coal;
                                }
                                else if (coaloriron==1){
                                    chunks[chunk_coord][make_tuple(x,y,z)] = iron_ore;
                                    //newchunks[chunk_coord] = 1;
                                    allchunks[make_tuple(x,y,z)] = iron_ore;
                                }
                            }
                            else {
                                // Retaining the old block
                                chunks[chunk_coord][make_tuple(x,y,z)] = allchunks[make_tuple(x,y,z)];

                            }
                        }


                    }
                }
            }
        }

        count+=1;
        if (count>numiter){

            int i = rand() % 10 + 1;
            if (i>5){
                break;
            }
        }

        double rotxz = 179*PerlinNoise_2D(currx,currz)-45;
        currx += int(round(step*cos(rotxz*3.14159/180)));
        currz += int(round(step*sin(rotxz*3.14159/180)));

        if (count < 7){
            curry -= step;
        }
        else{
            double roty = 90*PerlinNoise_3D(currx,curry,currz);
            curry -= int(round(step*cos(roty*3.14159/180)));
            if (curry < lowest){
                curry += int(round(step*cos(roty*3.14159/180)));
            }
        }

    }

}


float Noise(int x, int z){
    int n = x+z*57;
    n = (n<<13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1*(2.0 - float(t)/1073741824.0)/2.0 ;
}

float smoothedNoise(int x, int z){
    float corners = ( Noise(x-1, z-1)+Noise(x+1, z-1)+Noise(x-1, z+1)+Noise(x+1, z+1) ) / 16;
    float sides   = ( Noise(x-1, z)  +Noise(x+1, z)  +Noise(x, z-1)  +Noise(x, z+1) ) /  8;
    float center  =  Noise(x,z)/4;
    return corners + sides + center;
}

float PerlinNoise_2D(int x, int z){

    float total = 0;
    float p = 0.4;
    float frequency;
    float amplitude;

    int n = 5; // Number of octaves
    int f = 8;


    for(int i =0; i<n; i++){
        frequency = pow(2.0,i);
        amplitude = pow(p,i);
        if (x%f==0 && z%f==0){
            total = total + smoothedNoise(x * frequency, z * frequency) * amplitude;
        }
        else{
            total = total + Interpolate(x * frequency, z * frequency, f) * amplitude;
        }
    }

    return total;
}

float PerlinNoise_biomes(int x, int z){

    float total = 0;
    float p = 0.7;
    float frequency;
    float amplitude;

    int n = 3; // Number of octaves
    int f = 1;


    for(int i =0; i<n; i++){
        frequency = pow(3.0,i);
        amplitude = pow(p,i);
        if (x%f==0 && z%f==0){
            total = total + smoothedNoise(x * frequency, z * frequency) * amplitude;
        }
        else{
            total = total + Interpolate(x * frequency, z * frequency, f) * amplitude;
        }
    }

    return total;
}

float PerlinNoise_biomes2(int x){

    float total = 0;
    float p = 0.5;
    float frequency;
    float amplitude;

    int n = 1; // Number of octaves
    int f = 1;


    for(int i =0; i<n; i++){
        frequency = pow(2.0,i);
        amplitude = pow(p,i);
        if (x%f==0){
            total = total + smoothedNoise1D(x * frequency) * amplitude;
        }
        else{
            total = total + Interpolate1D(x * frequency, f) * amplitude;
        }
    }

    return total;
}


float Interpolate(int x, int z, int f){
    int ax = x - x%f;
    int bx = x + f - x%f;

    int az = z - z%f;
    int bz = z + f - z%f;

    float noise1 = smoothedNoise( ax, az);
    float noise2 = smoothedNoise( ax, bz);
    float noise3 = smoothedNoise( bx, az);
    float noise4 = smoothedNoise( bx, bz);

    float noisex1 = ((f - x%f)*noise1 + (x%f)*noise3)/f;
    float noisex2 = ((f - x%f)*noise2 + (x%f)*noise4)/f;
    float noise = ((f - z%f)*noisex1 + (z%f)*noisex2)/f;

    return  noise;
}


unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> >& Scene::getChunks(){
    //unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> > temp;
    //allchunks = temp;

//    for(unordered_map< tuple<int,int,int>, int> ::iterator itr = newchunks.begin(); itr!= newchunks.end(); itr++){
//        temp[itr->first] = chunks[itr->first];
//    }
//    allchunks = temp;
//    return allchunks;
    return chunks;
}



float Noise3D(int x, int y, int z){
    int n = x+y*29+z*57;
    n = (n<<13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1*(2.0 - float(t)/1073741824.0)/2.0 ;
}

float smoothedNoise3D(int x, int y, int z){
    float edges = ( Noise3D(x-1, y,z-1)+Noise3D(x+1,y,z-1)+ Noise3D(x-1,y, z+1)+ Noise3D(x+1,y,z+1) + Noise3D(x, y-1,z-1)+ Noise3D(x,y+1,z-1)+Noise3D(x,y-1, z+1)+Noise3D(x,y+1,z+1) + Noise3D(x-1, y-1,z)+Noise3D(x+1,y-1,z)+Noise3D(x-1,y+1, z)+Noise3D(x+1,y+1,z)) / 48;
    float faces   = ( Noise3D(x-1, y,z)  +Noise3D(x+1,y, z)  +Noise3D(x,y, z-1)  +Noise3D(x,y,z+1) +Noise3D(x,y+1, z)  +Noise3D(x,y-1,z) ) / 12;
    float center  =  Noise3D(x,y,z)/4;
    return edges + faces + center;
}

float PerlinNoise_3D(int x, int y, int z){

    float total = 0;
    float p = 0.4;
    float frequency;
    float amplitude;

    int n = 3; // Number of octaves
    int f = 8;


    for(int i =0; i<n; i++){
        frequency = pow(2.0,i);
        amplitude = pow(p,i);
        if (x%f==0&& y%f==0 && z%f==0){
            total = total + smoothedNoise3D(x * frequency, y * frequency, z * frequency) * amplitude;
        }
        else{
            total = total + Interpolate3D(x * frequency, y * frequency,z * frequency, f) * amplitude;
        }
    }

    return total;
}

float Interpolate3D(int x, int y, int z, int f){
    int ax = x - x%f;
    int bx = x + f - x%f;

    int ay = y - y%f;
    int by = y + f - y%f;

    int az = z - z%f;
    int bz = z + f - z%f;

    float noise1 = smoothedNoise3D( ax, ay, az);
    float noise2 = smoothedNoise3D( ax, ay, bz);
    float noise3 = smoothedNoise3D( bx, ay, az);
    float noise4 = smoothedNoise3D( bx, ay, bz);
    float noise5 = smoothedNoise3D( ax, by, az);
    float noise6 = smoothedNoise3D( ax, by, bz);
    float noise7 = smoothedNoise3D( bx, by, az);
    float noise8 = smoothedNoise3D( bx, by, bz);

    float noisex1 = ((f - x%f)*noise1 + (x%f)*noise3)/f;
    float noisex2 = ((f - x%f)*noise2 + (x%f)*noise4)/f;
    float noisex3 = ((f - x%f)*noise5 + (x%f)*noise7)/f;
    float noisex4 = ((f - x%f)*noise6 + (x%f)*noise8)/f;

    float noisez1 = ((f - z%f)*noisex1 + (z%f)*noisex2)/f;
    float noisez2 = ((f - z%f)*noisex3 + (z%f)*noisex4)/f;

    float noise = ((f - y%f)*noisez1 + (y%f)*noisez2)/f;

    return  noise;
}

float Noise1D(int n){

    n = (n<<13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1*(2.0 - float(t)/1073741824.0)/2.0 ;
}

float smoothedNoise1D(int x){
    float corners = ( Noise1D(x-1)+Noise1D(x+1)) / 4;
    float center  =  Noise1D(x)/2;
    return corners +  center;
}

float PerlinNoise_1D(int x){

    float total = 0;
    float p = 0.4;
    float frequency;
    float amplitude;

    int n = 3; // Number of octaves
    int f = 1;


    for(int i =0; i<n; i++){
        frequency = pow(2.0,i);
        amplitude = pow(p,i);
        if (x%f==0){
            total = total + smoothedNoise1D(x * frequency) * amplitude;
        }
        else{
            total = total + Interpolate1D(x * frequency, f) * amplitude;
        }
    }

    return total;
}

float PerlinNoise_1Dnew(int x){

    float total = 0;
    float p = 0.5;
    float frequency;
    float amplitude;

    int n = 1; // Number of octaves
    int f = 1;


    for(int i =0; i<n; i++){
        frequency = pow(2.0,i);
        amplitude = pow(p,i);
        if (x%f==0){
            total = total + smoothedNoise1D(x * frequency) * amplitude;
        }
        else{
            total = total + Interpolate1D(x * frequency, f) * amplitude;
        }
    }

    return total;
}

float Interpolate1D(int x, int f){
    int ax = x - x%f;
    int bx = x + f - x%f;

    float noise1 = smoothedNoise1D(ax);
    float noise2 = smoothedNoise1D(bx);

    float noise = ((f - x%f)*noise1 + (x%f)*noise2)/f;

    return  noise;
}

void Scene::create_biome(tuple<int,int,int> centre){
    unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> > mChunk;
    chunks = mChunk;
    int xc = get<0>(centre);
    int yc = get<1>(centre);
    int zc = get<2>(centre);
    float decide = PerlinNoise_biomes2(xc+zc);
    int radiusx = 10+round(18*PerlinNoise_biomes(xc,zc));
    int radiusz = 10+round(16*PerlinNoise_biomes(zc,xc));
    int extra = 10;
    //srand (time(NULL));
    int rn = rand() % 2;
    float biome = PerlinNoise_biomes2(xc-zc);

    tuple<int,int,int> chunk_coord;

    if (decide <= 0.52){
        for (int x= xc-radiusx-extra; x< xc+radiusx+extra; x++){
            for (int z= zc-radiusz-extra; z< zc+radiusz+extra; z++){
                float dist1 = (x-xc)*(x-xc)/float(radiusx*radiusx) + (z-zc)*(z-zc)/float(radiusz*radiusz);
                //int dist2 = (x-xc)*(x-xc)+(z-zc)*(z-zc);

                get<0>(chunk_coord) = int(floor(x/16.0));
                get<2>(chunk_coord) = int(floor(z/16.0));
                if (dist1< 1){

                    if (biome>=0.4 && biome<0.6){
                        color[make_tuple(x,yc,z)] = sand;
                        //height[make_tuple(x,z)] = round(sqrt(radius*radius-dist2)*PerlinNoise_2D(x, z));
                        height[make_tuple(x,z)] = 12+round(radiusx*(1-dist1)*PerlinNoise_2D(x, z));
                        for (int y = 0; y <= height[make_tuple(x,z)]; y++){
                            get<1>(chunk_coord) = int(floor((y+dimensions.y/2)/16.0));
                            chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = color[make_tuple(x,yc,z)];
                        }
                    }
                    else {
                        if (rn==1){
                            color[make_tuple(x,yc,z)] = snow;
                            //height[make_tuple(x,z)] = round(sqrt(radius*radius-dist2)*PerlinNoise_2D(x, z));
                            height[make_tuple(x,z)] = 3+round(9*PerlinNoise_2D(x, z));
                            for (int y = 0; y <= height[make_tuple(x,z)]; y++){
                                get<1>(chunk_coord) = int(floor((y+dimensions.y/2)/16.0));
                                chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = color[make_tuple(x,yc,z)];
                            }
                        }
                        else{
                            color[make_tuple(x,yc,z)] = water;
                            height[make_tuple(x,z)] = 2+round(1*PerlinNoise_2D(x, z));
                            for (int y = 0; y <= height[make_tuple(x,z)]; y++){
                                get<1>(chunk_coord) = int(floor((y+dimensions.y/2)/16.0));
                                chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = color[make_tuple(x,yc,z)];
                            }
                        }
                    }
                }
                else if (dist1>=1 && dist1<1.5){
                    if (biome>=0.4 && biome<0.6){
                        color[make_tuple(x,yc,z)] = sand;
                        height[make_tuple(x,z)] = 3+round(9*PerlinNoise_2D(x, z));
                        for (int y = 0; y <= height[make_tuple(x,z)]; y++){
                            get<1>(chunk_coord) = int(floor((y+dimensions.y/2)/16.0));
                            chunks[chunk_coord][make_tuple(x,y+dimensions.y/2,z)] = color[make_tuple(x,yc,z)];
                        }
                    }
                }
            }
        }
    }
}


int max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
