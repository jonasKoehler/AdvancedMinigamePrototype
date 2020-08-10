#pragma region system include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Renderer.h"
#include "Texture.h"
#include "Rect.h"
#include "Macro.h"
#pragma endregion

#pragma region constructor
// constructor
CRenderer::CRenderer(SDL_Window* _pWindow)
{
	// create sdl renderer
	m_pSdlRenderer = SDL_CreateRenderer(
		_pWindow,					// sdl window
		-1,							// driver index
		SDL_RENDERER_ACCELERATED |	// flags
		SDL_RENDERER_PRESENTVSYNC
	);
}
#pragma endregion

#pragma region destructor
// destructor
CRenderer::~CRenderer()
{
	// destroy sdl renderer
	SDL_DestroyRenderer(m_pSdlRenderer);
}
#pragma endregion

#pragma region public function
// clear screen
void CRenderer::ClearScreen()
{
	SDL_RenderClear(m_pSdlRenderer);
}

// render texture
void CRenderer::RenderTexture(CTexture* _pTexture, SRect* _pDstRect, float _angle, SRect* _pSrcRect, bool _inWorld, SVector2 _mirror)
{
	// if texture not valid return
	if (!_pTexture || !_pTexture->GetSdlTexture())
		return;

	// if source rect valid and width or height zero
	if (_pSrcRect && (!_pSrcRect->w || !_pSrcRect->h))
		// set source rect to nullptr to use whole texture
		_pSrcRect = nullptr;

	// destination rect
	SRect dstRect = SRect();

	// if destination rect valid and width or height zero
	if (_pDstRect && (!_pDstRect->w || !_pDstRect->h))
		// set destination rect to nullptr to use whole screen
		_pDstRect = nullptr;
	
	// if destination rect valid
	if (_pDstRect)
		// set destination rect values
		dstRect = *_pDstRect;

	// if rect is valid
	if (_pDstRect)
	{
		// set rotation point of texture to center
		SDL_Point rotationPoint;
		rotationPoint.x = _pDstRect->w * 0.5f;
		rotationPoint.y = _pDstRect->h * 0.5f;

		// flip texture
		SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

		// if mirror only horizontal flip horizontal
		if (_mirror.X && !_mirror.Y)
			flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

		// if mirror only vertical flip vertical
		else if (!_mirror.X && _mirror.Y)
			flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;

		// if mirror horizontal and vertical add 180 degree to rotation
		else if (_mirror.X && _mirror.Y)
			_angle += 180.0f;

		// if rendered in world space
		if (_inWorld)
		{
			// change destination rect values by zoom
			dstRect.x *= m_zoom;
			dstRect.y *= m_zoom;
			dstRect.w *= m_zoom;
			dstRect.h *= m_zoom;

			// move rect by screen size and camera position
			dstRect.x += ENGINE->GetWidth() * 0.5f - m_camera.X * m_zoom;
			dstRect.y += ENGINE->GetHeight() * 0.5f - m_camera.Y * m_zoom;

			// increase width and height because of float
			dstRect.w += 1;
			dstRect.h += 1;
		}

		// render texture with angle
		SDL_RenderCopyEx(
			m_pSdlRenderer,				// sdl renderer
			_pTexture->GetSdlTexture(),	// sdl texture
			_pSrcRect,					// source rect
			&dstRect,					// destination rect
			_angle,						// angle of rect
			&rotationPoint,				// rotation point of angle
			flip						// flip flag
		);

		// render debug rect
		if (DRAW_DEBUG)
		{
			SDL_SetRenderDrawColor(m_pSdlRenderer, 255, 0, 255, 255);
			SDL_RenderDrawRect(m_pSdlRenderer, &dstRect);
			SDL_SetRenderDrawColor(m_pSdlRenderer, 0, 0, 0, 255);
		}
	}

	// if rect not valid
	else
	{
		// render texture
		SDL_RenderCopy(
			m_pSdlRenderer,				// sdl renderer
			_pTexture->GetSdlTexture(),	// sdl texture
			_pSrcRect,					// source rect
			_pDstRect					// destination rect
		);
	}
}

// present rendered textures
void CRenderer::Present()
{
	SDL_RenderPresent(m_pSdlRenderer);
}
#pragma endregion