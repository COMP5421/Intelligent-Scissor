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

%costGraph = uint8(costGraph);
% 
% function [ CostGraph ] = Find_Cost( Image, Image_width, Image_length, Image_dim )
% 
% original_img = Image;
% Image = double(Image);
% 
% Dlink5_Filter = [0 0 0; 1/sqrt(2) 0 0; 0 -1/sqrt(2) 0];
% Dlink6_Filter = [0 0 0; 1/4 0 -1/4; 1/4 0 -1/4];
% Dlink7_Filter = [0 0 0; 0 0 1/sqrt(2); 0 -1/sqrt(2) 0];
% Dlink0_Filter = [0 1/4 1/4; 0 0 0; 0 -1/4 -1/4];
% 
% if Image_dim == 3
%     CostGraph_padding = zeros(Image_width*3+2,Image_length*3+2,3);
%     [width,length,~] = size(CostGraph_padding);
%     
%     Dlink5_rgb = zeros(Image_width,Image_length,3);
%     Dlink6_rgb = zeros(Image_width,Image_length,3);
%     Dlink7_rgb = zeros(Image_width,Image_length,3);
%     Dlink0_rgb = zeros(Image_width,Image_length,3);
% 
%     Dlink5_rgb(:,:,:) = abs(imfilter(Image(:,:,:),Dlink5_Filter));
%     Dlink6_rgb(:,:,:) = abs(imfilter(Image(:,:,:),Dlink6_Filter));
%     Dlink7_rgb(:,:,:) = abs(imfilter(Image(:,:,:),Dlink7_Filter));
%     Dlink0_rgb(:,:,:) = abs(imfilter(Image(:,:,:),Dlink0_Filter));
%     
%     Dlink5 = sqrt((Dlink5_rgb(:,:,1).^2+Dlink5_rgb(:,:,2).^2+Dlink5_rgb(:,:,3).^2)/3);
%     Dlink6 = sqrt((Dlink6_rgb(:,:,1).^2+Dlink6_rgb(:,:,2).^2+Dlink6_rgb(:,:,3).^2)/3);
%     Dlink7 = sqrt((Dlink7_rgb(:,:,1).^2+Dlink7_rgb(:,:,2).^2+Dlink7_rgb(:,:,3).^2)/3);
%     Dlink0 = sqrt((Dlink0_rgb(:,:,1).^2+Dlink0_rgb(:,:,2).^2+Dlink0_rgb(:,:,3).^2)/3);
%      
%     maxD = max([max(Dlink5(:)) max(Dlink6(:)) max(Dlink7(:)) max(Dlink0(:))]);
%     
%     for i = 1:Image_width
%         for j = 1:Image_length
%             CostGraph_padding(3*i,3*j,:) = original_img(i,j,:);
%             
%             CostGraph_padding(3*i+1,3*j-1,:) = (maxD-Dlink5(i,j))*sqrt(2);
%             CostGraph_padding(3*i+2,3*j-2,:) = CostGraph_padding(3*i+1,3*j-1,:);
%             
%             CostGraph_padding(3*i+1,3*j,:) = (maxD-Dlink6(i,j));
%             CostGraph_padding(3*i+2,3*j,:) = CostGraph_padding(3*i+1,3*j,:);
%             
%             CostGraph_padding(3*i+1,3*j+1,:) = (maxD-Dlink7(i,j))*sqrt(2);
%             CostGraph_padding(3*i+2,3*j+2,:) = CostGraph_padding(3*i+1,3*j+1,:);
%             
%             CostGraph_padding(3*i,3*j+1,:) = (maxD-Dlink0(i,j));
%             CostGraph_padding(3*i,3*j+2,:) = CostGraph_padding(3*i,3*j+1,:);
%         end
%     end
% 
%     CostGraph = CostGraph_padding(2:width-1,2:length-1,:);
%     
%     CostGraph_Mid = ones(size(CostGraph))*255;
%     CostGraph_Mid(3:end-2,3:end-2,:) = CostGraph(3:end-2,3:end-2,:);
%     CostGraph = CostGraph_Mid;
%     
% else
%     CostGraph_padding = zeros(Image_width*3+2,Image_length*3+2);
%     [width,length] = size(CostGraph_padding);
%     
%     Dlink5 = abs(imfilter(Image,Dlink5_Filter));
%     Dlink6 = abs(imfilter(Image,Dlink6_Filter));
%     Dlink7 = abs(imfilter(Image,Dlink7_Filter));
%     Dlink0 = abs(imfilter(Image,Dlink0_Filter));
%      
%     maxD = max([max(Dlink5(:)) max(Dlink6(:)) max(Dlink7(:)) max(Dlink0(:))]);
%     
%     for i = 1:Image_width
%         for j = 1:Image_length
%             
%             CostGraph_padding(3*i,3*j) = original_img(i,j);
%             
%             CostGraph_padding(3*i+1,3*j-1) = (maxD-Dlink5(i,j))*sqrt(2);
%             CostGraph_padding(3*i+2,3*j-2) = CostGraph_padding(3*i+1,3*j-1);
%             
%             CostGraph_padding(3*i+1,3*j) = (maxD-Dlink6(i,j));
%             CostGraph_padding(3*i+2,3*j) = CostGraph_padding(3*i+1,3*j);
%             
%             CostGraph_padding(3*i+1,3*j+1) = (maxD-Dlink7(i,j))*sqrt(2);
%             CostGraph_padding(3*i+2,3*j+2) = CostGraph_padding(3*i+1,3*j+1);
%             
%             CostGraph_padding(3*i,3*j+1) = (maxD-Dlink0(i,j));
%             CostGraph_padding(3*i,3*j+2) = CostGraph_padding(3*i,3*j+1);
%         end
%     end
%     
%     CostGraph = CostGraph_padding(2:width-1,2:length-1);
%     
%     CostGraph_Mid = ones(size(CostGraph))*255;
%     CostGraph_Mid(3:end-2,3:end-2) = CostGraph(3:end-2,3:end-2);
%     CostGraph = CostGraph_Mid;
% end
% 
% end



