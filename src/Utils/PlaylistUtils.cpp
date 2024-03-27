#include "Utils/PlaylistUtils.hpp"
#include "scotland2/shared/loader.hpp"
#include "logging.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/BeatmapLevelPack.hpp"
#include "GlobalNamespace/BeatmapLevelsModel.hpp"
#include "System/Collections/Generic/IReadOnlyList_1.hpp"

#include "songcore/shared/SongCore.hpp"

#include "playlistcore/shared/PlaylistCore.hpp"

namespace BetterSongList::PlaylistUtils {
    // we link to the playlist lib so it's always available
    static bool hasPlaylistLib = true;
    bool get_hasPlaylistLib() {
        return hasPlaylistLib;
    }

    SafePtr<Dictionary<StringW, GlobalNamespace::BeatmapLevelPack*>> builtinPacks;
    Dictionary<StringW, GlobalNamespace::BeatmapLevelPack*>* get_builtinPacks() {
        if (!builtinPacks) {
            return nullptr;
        }
        return builtinPacks.ptr();
    }

    void Init() {
        INFO("HAHABALL we don't need to init anything cause playlist mod is required on quest :)");
    }

    GlobalNamespace::BeatmapLevelPack* GetPack(StringW packID) {
        if (!packID) return nullptr;
        static std::string customLevelPackId = "custom_levelPack_CustomLevels";
        static std::string customWipLevelPackId = "custom_levelPack_CustomWIPLevels";
        if (packID == customLevelPackId) {
            return SongCore::API::Loading::GetCustomLevelPack();
        } else if (packID == customWipLevelPackId) {
            return SongCore::API::Loading::GetCustomWIPLevelPack();
        }

        if (!get_builtinPacks()) {
            builtinPacks = Dictionary<StringW, GlobalNamespace::BeatmapLevelPack*>::New_ctor();
            /*auto levelsModels = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::BeatmapLevelsModel*>();
            if (levelsModels) {
                auto levelModel = levelsModels.front();
                auto ostPacks = levelModel.value()->ostAndExtrasBeatmapLevelsRepository->beatmapLevelPacks->i___System__Collections__Generic__IEnumerable_1_T_();
                auto dlcPacks = levelModel.value()->dlcBeatmapLevelsRepository->beatmapLevelPacks->i___System__Collections__Generic__IEnumerable_1_T_();
                auto packs = ListW<GlobalNamespace::BeatmapLevelPack*>::New();
                packs->AddRange(ostPacks);
                packs->AddRange(dlcPacks);

                for (auto p : packs) {
                    builtinPacks->Add(p->packID, p);
                }
            }*/
        }

        GlobalNamespace::BeatmapLevelPack* v = nullptr;
        if (get_builtinPacks()->TryGetValue(packID, byref(v))) {
            return v;
        } else if (hasPlaylistLib) {
            auto pls = PlaylistCore::GetLoadedPlaylists();
            for (auto pl : pls) {
                if (pl->playlistCS) {
                    if (pl->playlistCS->packID == packID) {
                        return pl->playlistCS;
                    }
                }
            }
        }

        return nullptr;
    }

    ArrayW<GlobalNamespace::BeatmapLevel*> GetLevelsForLevelCollection(GlobalNamespace::BeatmapLevelPack* levelCollection) {
        return levelCollection ? levelCollection->beatmapLevels : ArrayW<GlobalNamespace::BeatmapLevel*>(il2cpp_array_size_t(0));
    }
}