/*
* Worked on by Adam Aronow
*/

#include "raylib.h"
#include "raymath.h"
#include "vector"

const float defaultCamWidth = 320;
const float defaultCamHeight = 180;

class TextureHandler
{
	private:

	public:
	TextureHandler( )
	{

	}
};

class Sprite
{
	protected:
	Texture2D texture;
	Vector2 centeredPosition;
	Vector2 realPosition;
	int scale = 1;
	float rotation = 0;
	Vector2 pivotPoint;
	Color tint = WHITE;

	public:
	Rectangle boundingRect;

	Sprite( )
	{

	}

	Sprite( Texture2D texture, Vector2 position )
	{
		this->texture = texture;
		setPosition( position );
	}

	Vector2 getPosition( )
	{
		return centeredPosition;
	}

	void setPosition( Vector2 position )
	{
		centeredPosition = position;
		realPosition = Vector2 { position.x - texture.width / 2, position.y - texture.height / 2 };
		boundingRect = { realPosition.x, realPosition.y, ( float ) texture.width, ( float ) texture.height };
	}

	void render( Vector2 cameraPosition )
	{
		DrawTextureEx( texture, Vector2Subtract( realPosition, cameraPosition ), rotation, scale, tint );
	}
};

class CustomCamera
{
	private:
	std::vector<Sprite*> buffer;
	RenderTexture2D renderTexture;
	Vector2 position;
	Vector2 topLeft;
	Vector2 size;
	float renderScale;
	Rectangle viewRectangle;
	public:
	CustomCamera( Vector2 position, Vector2 size, float renderScale )
	{
		buffer = { };
		renderTexture = LoadRenderTexture( (int) size.x, ( int ) size.y );
		this->size = size;
		setPosition( position );
		this->renderScale = renderScale;
		viewRectangle = { position.x - size.x / 2, position.y - size.y / 2, size.x, size.y };
	}
	CustomCamera( Vector2 size, float renderScale ) : CustomCamera( Vector2 { 0, 0 }, size, renderScale )
	{;}
	CustomCamera( ) : CustomCamera( Vector2 { defaultCamWidth, defaultCamHeight }, 1.0f )
	{;}

	void addToBuffer( Sprite* sprite )
	{
		buffer.push_back( sprite );
	}

	Vector2 getPosition( )
	{
		return position;
	}

	Rectangle setPosition( Vector2 position )
	{
		this->position = position;
		this->topLeft = { position.x - size.x / 2, position.y - size.y / 2 };
		viewRectangle = { topLeft.x, topLeft.y, size.x, size.y };
		return viewRectangle;
	}

	void prepareRender( )
	{
		// Culling sprites that aren't within the camera's view
		// Iteration has to occur backwards because indices are shifted back when deleting elements
		for ( int i = buffer.size( ) - 1; i >= 0; i-- )
		{
			if ( !CheckCollisionRecs( viewRectangle, buffer.at( i )->boundingRect ) )
			{
				buffer.erase( buffer.begin() + i );
			}
		}

		// TODO: Implement layer sorting
      
		// Rendering everything in the buffer to a texture
		BeginTextureMode( renderTexture );
		ClearBackground( BLACK );
		for ( Sprite *sprite : buffer )
		{
			sprite->render( topLeft );
		}
		buffer.clear( );
		EndTextureMode( );
	}

	void renderToScreen( )
	{
		DrawTextureEx( renderTexture.texture, { 0.0f, 0.0f }, 0.0f, renderScale, WHITE );
	}
};

class ScreenHandler
{
	private:
	int width = 1280;
	int height = 720;

	public:
	std::vector<CustomCamera*> cameras = {};

	ScreenHandler( )
	{
		InitWindow( width, height, "test" );
		SetTargetFPS( 60 );
	}

	void renderAll( )
	{
		for ( CustomCamera *camera : cameras )
		{
			camera->prepareRender( );
		}

		BeginDrawing( );
		ClearBackground( BLACK );
		for ( CustomCamera *camera : cameras )
		{
			camera->renderToScreen( );
		}
		EndDrawing( );
	}
};