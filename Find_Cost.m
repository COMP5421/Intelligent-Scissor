function [costGraph] = Find_Cost(img, height, width, dim)
img=double(img);
imgPadZero = zeros(height+2, width+2, dim);
costGraph = zeros(height*3, width*3, dim);

for i = 1:height
    for j = 1:width
        imgPadZero(i+1, j+1, :) = img(i, j, :);
    end
end

for i = 1:height
    for j = 1:width
        costGraph(3*i-1, 3*j-1, :) = img(i, j, :);
        costGraph(3*i-1, 3*j, :) = abs(imgPadZero(i, j+1, :)+imgPadZero(i, j+2, :)-imgPadZero(i+2, j+1, :)-imgPadZero(i+2, j+2, :))/4;
        costGraph(3*i-2, 3*j, :) = abs(imgPadZero(i, j+1, :)-imgPadZero(i+1, j+2, :))/sqrt(2);
        costGraph(3*i-2, 3*j-1, :) = abs(imgPadZero(i+1, j, :)+imgPadZero(i, j, :)-imgPadZero(i, j+2, :)-imgPadZero(i+1, j+2, :))/4;
        costGraph(3*i-2, 3*j-2, :) = abs(imgPadZero(i+1, j, :)-imgPadZero(i, j+1, :))/sqrt(2);
        costGraph(3*i-1, 3*j-2, :) = abs(imgPadZero(i+2, j, :)+imgPadZero(i+2, j+1, :)-imgPadZero(i, j, :)-imgPadZero(i, j+1, :))/4;
        costGraph(3*i, 3*j-2, :) = abs(imgPadZero(i+2, j+1, :)-imgPadZero(i+1, j, :))/sqrt(2);
        costGraph(3*i, 3*j-1, :) = abs(imgPadZero(i+1, j+2, :)+imgPadZero(i+2, j+2, :)-imgPadZero(i+1, j, :)-imgPadZero(i+2, j, :))/4;
        costGraph(3*i, 3*j, :) = abs(imgPadZero(i+2, j+1, :)-imgPadZero(i+1, j+2, :))/sqrt(2);
        
        if dim==3
            costGraph(3*i-1, 3*j, :) = sqrt((costGraph(3*i-1, 3*j, 1)*costGraph(3*i-1, 3*j, 1)+costGraph(3*i-1, 3*j, 2)*costGraph(3*i-1, 3*j, 2)+costGraph(3*i-1, 3*j, 3)*costGraph(3*i-1, 3*j, 3))/3);
            costGraph(3*i-2, 3*j, :) = sqrt((costGraph(3*i-2, 3*j, 1)*costGraph(3*i-2, 3*j, 1)+costGraph(3*i-2, 3*j, 2)*costGraph(3*i-2, 3*j, 2)+costGraph(3*i-2, 3*j, 3)*costGraph(3*i-2, 3*j, 3))/3);
            costGraph(3*i-2, 3*j-1, :) = sqrt((costGraph(3*i-2, 3*j-1, 1)*costGraph(3*i-2, 3*j-1, 1)+costGraph(3*i-2, 3*j-1, 2)*costGraph(3*i-2, 3*j-1, 2)+costGraph(3*i-2, 3*j-1, 3)*costGraph(3*i-2, 3*j-1, 3))/3);
            costGraph(3*i-2, 3*j-2, :) = sqrt((costGraph(3*i-2, 3*j-2, 1)*costGraph(3*i-2, 3*j-2, 1)+costGraph(3*i-2, 3*j-2, 2)*costGraph(3*i-2, 3*j-2, 2)+costGraph(3*i-2, 3*j-2, 3)*costGraph(3*i-2, 3*j-2, 3))/3);
            costGraph(3*i-1, 3*j-2, :) = sqrt((costGraph(3*i-1, 3*j-2, 1)*costGraph(3*i-1, 3*j-2, 1)+costGraph(3*i-1, 3*j-2, 2)*costGraph(3*i-1, 3*j-2, 2)+costGraph(3*i-1, 3*j-2, 3)*costGraph(3*i-1, 3*j-2, 3))/3);
            costGraph(3*i, 3*j-2, :) = sqrt((costGraph(3*i, 3*j-2, 1)*costGraph(3*i, 3*j-2, 1)+costGraph(3*i, 3*j-2, 2)*costGraph(3*i, 3*j-2, 2)+costGraph(3*i, 3*j-2, 3)*costGraph(3*i, 3*j-2, 3))/3);
            costGraph(3*i, 3*j-1, :) = sqrt((costGraph(3*i, 3*j-1, 1)*costGraph(3*i, 3*j-1, 1)+costGraph(3*i, 3*j-1, 2)*costGraph(3*i, 3*j-1, 2)+costGraph(3*i, 3*j-1, 3)*costGraph(3*i, 3*j-1, 3))/3);
            costGraph(3*i, 3*j, :) = sqrt((costGraph(3*i, 3*j, 1)*costGraph(3*i, 3*j, 1)+costGraph(3*i, 3*j, 2)*costGraph(3*i, 3*j, 2)+costGraph(3*i, 3*j, 3)*costGraph(3*i, 3*j, 3))/3);
    
        end
    end
end

maxD = max(max(max(costGraph)));

for i = 1:height
    for j = 1:width
        costGraph(3*i-1, 3*j, :) = (maxD-costGraph(3*i-1, 3*j, :))*1;
        costGraph(3*i-2, 3*j, :) = (maxD-costGraph(3*i-2, 3*j, :))*sqrt(2);
        costGraph(3*i-2, 3*j-1, :) = (maxD-costGraph(3*i-2, 3*j-1, :))*1;
        costGraph(3*i-2, 3*j-2, :) = (maxD-costGraph(3*i-2, 3*j-2, :))*sqrt(2);
        costGraph(3*i-1, 3*j-2, :) = (maxD-costGraph(3*i-1, 3*j-2, :))*1;
        costGraph(3*i, 3*j-2, :) = (maxD-costGraph(3*i, 3*j-2, :))*sqrt(2);
        costGraph(3*i, 3*j-1, :) = (maxD-costGraph(3*i, 3*j-1, :))*1;
        costGraph(3*i, 3*j, :) = (maxD-costGraph(3*i, 3*j, :))*sqrt(2);
    end
end

end
