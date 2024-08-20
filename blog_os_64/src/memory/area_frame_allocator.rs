use super::{Frame,FrameAllocator};

use multiboot2::{MemoryArea, MemoryAreaTypeId};

pub struct AreaFrameAllocator{
    next_free_frame:Frame,
    current_area:Option<&'static MemoryArea>,
    areas:MemoryAreaTypeId
}