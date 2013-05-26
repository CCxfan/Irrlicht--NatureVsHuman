/*
Copyright (c) 2008 Nils Daumann

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "PostProcessing.h"
#include <string>

void PostProcessing_SetShaderConstants::OnSetConstants(video::IMaterialRendererServices *services, s32 userdata)
{
    if(userdata == 0)
    {
        // set the materialparameters
        services->setPixelShaderConstant("vecValues",shaderparameters, 8);
    }
    else
    {
        int i;
        c8 *constname;

        // set the materialparameters
        for(i = 0; i < 8; i++)
        {
            constname = new char[strlen("Value") + (int)log(i+1) + 2];
            snprintf(constname, strlen("Value") + (int)log(i+1) + 2, "%s%d", "Value", i);

            services->setPixelShaderConstant((const c8*)constname,&shaderparameters[i], 1);

            delete[] constname;
        }

        //set Textures for openGL Shaders
        int texture = 0;
        services->setPixelShaderConstant("Texture0",(float*)&texture, 1);
        texture += 1;
        services->setPixelShaderConstant("Texture1",(float*)&texture, 1);
    }
}

PostProcessing::PostProcessing(scene::ISceneManager *smgr, const c8 *filename_dx, video::E_PIXEL_SHADER_TYPE type_ps, s32 res_x, s32 res_y, PostProcessing *previous)
{
    driver = smgr->getVideoDriver();

    if(driver->getDriverType() == video::EDT_DIRECT3D9)
    {
        vertices[0] = video::S3DVertex(-1.0f, -1.0f, 0.0f,1,1,0, video::SColor(255,0,255,255), 0.0f, 1.0f);
        vertices[1] = video::S3DVertex(-1.0f,  1.0f, 0.0f,1,1,0, video::SColor(255,0,255,255), 0.0f, 0.0f);
        vertices[2] = video::S3DVertex( 1.0f,  1.0f, 0.0f,1,1,0, video::SColor(255,0,255,255), 1.0f, 0.0f);
        vertices[3] = video::S3DVertex( 1.0f, -1.0f, 0.0f,1,1,0, video::SColor(255,0,255,255), 1.0f, 1.0f);

        video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
        scenemgr = smgr;

        prevstage = previous;
        nextstage = NULL;

        setShaderParameters();
        shadercallback.setShaderParameters(&shaderparameters[0]);

        matid = gpu->addHighLevelShaderMaterialFromFiles
                (
                    "PP_DX_Vertex.fx",
                    "main",
                    video::EVST_VS_1_1,
                    filename_dx,
                    "main",
                    type_ps,
                    &shadercallback,
                    video::EMT_SOLID,
                    0
                );


        firstmap = driver->addRenderTargetTexture(core::dimension2d<u32>(res_x,res_y),"RTT1",irr::video::ECF_A8R8G8B8);
        secondmap = NULL;
        material.Wireframe = false;
        material.Lighting = false;
        material.setTexture(0,firstmap);
        material.TextureLayer[0].TextureWrapU = video::ETC_CLAMP;
        material.TextureLayer[0].TextureWrapV = video::ETC_CLAMP;
        material.MaterialType = (video::E_MATERIAL_TYPE)matid;
    }
}

PostProcessing::~PostProcessing()
{
    if(nextstage != NULL)
    {
        delete nextstage;
    }
}

PostProcessing *PostProcessing::addMaterial(const c8 *filename_dx,
        video::E_PIXEL_SHADER_TYPE type_ps, s32 res_x, s32 res_y, s32 position)
{
    PostProcessing *tempnextstage;

    if(position == -1)
    {
        tempstage = nextstage;
        if(tempstage != NULL)
        {
            for(tempnextstage = nextstage; tempnextstage != NULL; tempnextstage = tempstage->getNextStage())
            {
                if(tempnextstage != NULL)
                {
                    tempstage = tempnextstage;
                }
            }
        }
        else
        {
            tempstage = this;
        }

        tempnextstage = new PostProcessing(scenemgr,filename_dx,type_ps,res_x,res_y,tempstage);

        tempstage->setNextStage(tempnextstage);
    }/*else
	{
		if(position != 0)
		{
			PostProcessing *tempnextstage;
            tempstage = nextstage;
            if(tempstage != NULL)
            {
                for(tempnextstage = prevstage; tempnextstage != NULL; tempnextstage = tempstage->getPrevStage())
                {
                    if(tempnextstage != NULL)
                    {
                        tempstage = tempnextstage;
                    }
                }
            }else
            {
                tempstage = this;
            }


			int i;
			for(i = 0; i < position; i++)
			{
				if(tempstage->getNextStage() != NULL)
				{
					tempstage = tempstage->getNextStage();
				}
			}

			tempnextstage = tempstage->getNextStage();

			tempstage->setNextStage(new PostProcessing(scenemgr,filename_gl,filename_dx,type_ps,res_x,res_y,tempstage));

			tempnextstage->setPrevStage(tempstage->getNextStage());
		}else
		{

		}
	}*/

    return tempstage->getNextStage();
}

void PostProcessing::renderEffect()
{
    u16 indices[] = {0,1,2,0,2,3};
    driver->setMaterial(material);

    if(nextstage != NULL)
    {
        driver->setRenderTarget(nextstage->getFirstMap(), true, true, video::SColor(255,150,180,255));
        driver->drawIndexedTriangleList(vertices, 6, indices, 2);
        driver->setRenderTarget(0);

        nextstage->renderEffect();
    }
    else
    {
        driver->drawIndexedTriangleList(vertices, 6, indices, 2);
    }
}
